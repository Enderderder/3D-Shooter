/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : server.cpp
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

//Library Includes
#include <WS2tcpip.h>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <sstream>


//Local Includes
#include "Utility.h"
#include "network.h"
#include "consoletools.h"
#include "socket.h"
#include "TextLabel.h"

//Local Includes
#include "server.h"
#include "SceneMgr.h"

static CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();

CServer::CServer()
	:m_pcPacketData(0),
	m_pServerSocket(0)
{
	ZeroMemory(&m_ClientAddress, sizeof(m_ClientAddress));
}

CServer::~CServer()
{
	delete m_pConnectedClients;
	m_pConnectedClients = 0;

	delete m_pServerSocket;
	m_pServerSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;
	
	delete[] m_pcPacketData;
	m_pcPacketData = 0;
}

bool CServer::Initialise()
{
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	
	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pServerSocket = new CSocket();

	//Get the port number to bind the socket to
	unsigned short _usServerPort = DEFAULT_SERVER_PORT;
	//unsigned short _usServerPort = QueryPortNumber(DEFAULT_SERVER_PORT);	//To ask user to enter server port

	//Initialise the socket to the local loop back address and port number
	if (!m_pServerSocket->Initialise(_usServerPort))
	{
		return false;
	}

	//Qs 2: Create the map to hold details of all connected clients
	m_pConnectedClients = new std::map < std::string, TClientDetails >() ;

	return true;
}

bool CServer::AddClient(std::string _strClientName)
{
	//TO DO : Add the code to add a client to the map here...
	std::string stringtemp;
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		//Check to see that the client to be added does not already exist in the map, 
		if(it->first == ToString(m_ClientAddress))
		{
			return false;
		}
		//also check for the existence of the username
		else if (it->second.m_strName == _strClientName)
		{
			return false;
		}
	}
	//Add the client to the map.
	TClientDetails _clientToAdd;
	m_pClientName = _strClientName;
	_clientToAdd.m_strName = _strClientName;
	_clientToAdd.m_ClientAddress = this->m_ClientAddress;

	std::string _strAddress = ToString(m_ClientAddress);
	m_pConnectedClients->insert(std::pair < std::string, TClientDetails > (_strAddress, _clientToAdd));
	return true;
}

bool CServer::SendData(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;
	
	int iNumBytes = sendto(
		m_pServerSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet target
		sizeof(m_ClientAddress)							// size of the above address struct.
		);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

void CServer::ReceiveData(char* _pcBufferToReceiveData)
{
	
	int iSizeOfAdd = sizeof(m_ClientAddress);
	int _iNumOfBytesReceived;
	int _iPacketSize;

	//Make a thread local buffer to receive data into
	char _buffer[MAX_MESSAGE_LENGTH];

	while (true)
	{
		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
			m_pServerSocket->GetSocketHandle(),		// client-end socket being used to read from
			_buffer,								// incoming packet to be filled
			MAX_MESSAGE_LENGTH,						// length of incoming packet to be filled
			0,										// flags
			reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet source
			&iSizeOfAdd								// size of the above address struct.
		);
		if (_iNumOfBytesReceived < 0)
		{
			int _iError = WSAGetLastError();
			ErrorRoutines::PrintWSAErrorInfo(_iError);
			return;
		}
		else
		{
			_iPacketSize = static_cast<int>(strlen(_buffer)) + 1;
			strcpy_s(_pcBufferToReceiveData, _iPacketSize, _buffer);
			char _IPAddress[100];
			inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));
			
			std::cout << "Server Received \"" << _pcBufferToReceiveData << "\" from " <<
				_IPAddress << ":" << ntohs(m_ClientAddress.sin_port) << std::endl;
			//Push this packet data into the WorkQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield();
		
	} //End of while (true)
}

void CServer::GetRemoteIPAddress(char* _pcSendersIP)
{
	char _temp[MAX_ADDRESS_LENGTH];
	int _iAddressLength;
	inet_ntop(AF_INET, &(m_ClientAddress.sin_addr), _temp, sizeof(_temp));
	_iAddressLength = static_cast<int>(strlen(_temp)) + 1;
	strcpy_s(_pcSendersIP, _iAddressLength, _temp);
}

unsigned short CServer::GetRemotePort()
{
	return ntohs(m_ClientAddress.sin_port);
}

void CServer::ProcessData(char* _pcDataReceived)
{
	TPacket _packetRecvd, _packetToSend;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	switch (_packetRecvd.MessageType)
	{
	
	case HANDSHAKE:
	{
		
		if (AddClient(_packetRecvd.MessageContent))
		{
			_packetToSend.Serialize(HANDSHAKE, "Handshake Received");
			SendData(_packetToSend.PacketData);
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (it->first == ToString(m_ClientAddress))
				{
					m_ClientAddress = it->second.m_ClientAddress;

					std::string stringtemp = "Welcome " + m_pClientName + " to the chat";
					strcpy_s(charNameptr, stringtemp.c_str());
					_packetToSend.Serialize(DATA, charNameptr);
					SendData(_packetToSend.PacketData);
				}
			}
			CurrentUsers(_packetToSend);
			
		}
		else
		{
			_packetToSend.Serialize(USERNAME, "Username is already taken");
			SendData(_packetToSend.PacketData);
		}

		break;
	}
	case LOBBYTYPE:
	{

			cSceneMgr->GetCurrentScene()->TextTemp = new CTextLabel("Arial", "Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - (100 * i) - 100));
			cSceneMgr->GetCurrentScene()->TextTemp->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
			cSceneMgr->GetCurrentScene()->m_pText.push_back(cSceneMgr->GetCurrentScene()->TextTemp);

			std::stringstream strs;
			strs << /*m_pConnectedClients->end()->second.m_strName <<*/ "Connected";
			std::string stringtemp = strs.str();
			strcpy_s(charNameptr, stringtemp.c_str());

			i++;

		_packetToSend.Serialize(LOBBYTYPE, charNameptr);
		SendData(_packetToSend.PacketData);

		break;
	} 
	case DATA:
	{

		int charCompereHelp = strcmp(strcompereHelp, _packetRecvd.MessageContent);
		int charCompereQuit = strcmp(stCompereQuit, _packetRecvd.MessageContent);

		//Checks to see if the clinets is sending a command
		if (charCompereHelp == 0 || charCompereQuit == 0)
		{
			//checks if it is a help command
			if (charCompereHelp == 0)
			{
				_packetToSend.Serialize(COMMAND, "HELP");
				SendData(_packetToSend.PacketData);

				break;
			}

			std::string stringaNametemp;

			//checks if it is a quit command
			if (charCompereQuit == 0)
			{
				for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
				{
					if (it->first == ToString(m_ClientAddress))
					{
						stringaNametemp = it->second.m_strName;

						//deletes the client that just quit from map 
						m_pConnectedClients->erase(it);

						_packetToSend.Serialize(COMMAND, "QUIT");
						SendData(_packetToSend.PacketData);
						break;
					}
					
				}

				//tell the console who has has quit then all curent connected users
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				std::cout << stringaNametemp << " has quit the chat" << std::endl << std::endl;

				std::cout << " Current Connected Users:" << std::endl;
				

				for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
				{
				

					//all clinets display ____ has quit the chat
					if (it->first != ToString(m_ClientAddress))
					{

						m_ClientAddress = it->second.m_ClientAddress;

						std::string stringtemp = stringaNametemp + " has quit the chat";
						strcpy_s(charNameptr, stringtemp.c_str());
						_packetToSend.Serialize(DATA, charNameptr);
						SendData(_packetToSend.PacketData);

						
					}

					//Displays current users to server
					std::cout << it->second.m_strName << std::endl;
				}
				break;
			}

		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		else 
		{
			//Messages display to all users
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				
				//all clinets display everyone messages
				if (it->first == ToString(m_ClientAddress))
				{

					for (auto It = m_pConnectedClients->begin(); It != m_pConnectedClients->end(); ++It)
					{
						m_ClientAddress = It->second.m_ClientAddress;
						
						std::string stringtemp = it->second.m_strName + "> " + _packetRecvd.MessageContent;
						strcpy_s(charNameptr, stringtemp.c_str());
						_packetToSend.Serialize(DATA, charNameptr);
						SendData(_packetToSend.PacketData);
					}
					break;
				}


			}
		}
		

		/*_packetToSend.Serialize(DATA, "TEST MESSAGE");
		SendData(_packetToSend.PacketData);*/

		break;
	}

	case BROADCAST:
	{
		std::cout << "Received a broadcast packet" << std::endl;
		//Just send out a packet to the back to the client again which will have the server's IP and port in it's sender fields
		_packetToSend.Serialize(BROADCAST, "I'm here!");
		SendData(_packetToSend.PacketData);
		break;
	}
	case KEEPALIVE:
	{

		break;
	}

	default:
		break;

	}
}

CWorkQueue<char*>* CServer::GetWorkQueue()
{
	return m_pWorkQueue;
}

void CServer::CurrentUsers(TPacket _packetToSend)
{
	//Displays all cureent users
	_packetToSend.Serialize(DATA, "Connected Users:");
	SendData(_packetToSend.PacketData);
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		if (it->first != ToString(m_ClientAddress))
		{
			strcpy_s(charNameptr, it->second.m_strName.c_str());
			_packetToSend.Serialize(DATA, charNameptr);
			SendData(_packetToSend.PacketData);
		}
	}
}
