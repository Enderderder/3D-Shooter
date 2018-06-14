/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CNetworkMgr.cpp
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Include --------------------------------------------------------------------------------
#include "CNetworkMgr.h"

// Network Include -----------------------------------------------------------------------------
#include "consoletools.h"
#include "network.h"
#include "client.h"
#include "server.h"
#include "InputLineBuffer.h"
#include <functional>

// Global Variable -----------------------------------------------------------------------------
CInputLineBuffer _InputBuffer(MAX_MESSAGE_LENGTH);
CNetwork& _rNetwork = CNetwork::GetInstance();

//A pointer to hold a client instance
CClient* _pClient = nullptr;
//A pointer to hold a server instance
CServer* _pServer = nullptr;

char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
									  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));

char* _pcPacketData = 0; //A local buffer to receive packet data info

CNetworkMgr::CNetworkMgr()
{
}


CNetworkMgr::~CNetworkMgr()
{
	//m_ClientReceiveThread.join();
	//m_ServerReceiveThread.join();
}

void CNetworkMgr::StartNetwork()
{
	
		
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");

		

	unsigned char _ucChoice;
		
	

	//Get the instance of the network
		
	_rNetwork.StartUp();

	// query, is this to be a client or a server?
	_ucChoice = QueryOption("Do you want to run a client or server (C/S)?", "CS");
	switch (_ucChoice)
	{
	case 'C':
	{
		_eNetworkEntityType = CLIENT;
		break;
	}
	case 'S':
	{
		_eNetworkEntityType = SERVER;
		break;
	}
	default:
	{
		std::cout << "This is not a valid option" << std::endl;
		break;
	}
	}

	if (!_rNetwork.GetInstance().Initialise(_eNetworkEntityType))
	{
		std::cout << "Unable to initialise the Network........Press any key to continue......";
		_getch();
		return;
	}

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{

		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		m_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
		m_ClientReceiveThread.detach();
	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{

		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		m_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
		m_ServerReceiveThread.detach();
	}

	//	std::thread Thread_obj2(&CNetworkMgr::ServerMainLoop);

	//End of while network is Online
	//Thread_obj1.join();
	//Thread_obj2.join();


	//Shut Down the Network
	//_rNetwork.ShutDown();
	//_rNetwork.DestroyObject();

	//delete[] _pcPacketData;
}

void CNetworkMgr::ClientMainLoop()
{
	while (_rNetwork.IsOnline())
	{
		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());

		//Prepare for reading input from the user
		_InputBuffer.PrintToScreenTop();

		//Get input from the user
		if (_InputBuffer.Update())
		{
			// we completed a message, lets send it:
			int _iMessageSize = static_cast<int>(strlen(_InputBuffer.GetString()));

			//Put the message into a packet structure
			TPacket _packet;
			_packet.Serialize(DATA, const_cast<char*>(_InputBuffer.GetString())); //Hardcoded username; change to name as taken in via user input.
			_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
			//Clear the Input Buffer
			_InputBuffer.ClearString();
			//Print To Screen Top
			_InputBuffer.PrintToScreenTop();
		}
		if (_pClient != nullptr)
		{
			//If the message queue is empty 
			if (_pClient->GetWorkQueue()->empty())
			{
				//Don't do anything
			}
			else
			{
				//Retrieve off a message from the queue and process it
				std::string temp;
				_pClient->GetWorkQueue()->pop(temp);
				_pClient->ProcessData(const_cast<char*>(temp.c_str()));
			}
		}


	}

}

void CNetworkMgr::ServerMainLoop()
{
	if (_rNetwork.IsOnline())
	{
		if (_pServer != nullptr)
		{
			if (!_pServer->GetWorkQueue()->empty())
			{
				_rNetwork.GetInstance().GetNetworkEntity()->GetRemoteIPAddress(_cIPAddress);
				//std::cout << _cIPAddress
				//<< ":" << _rNetwork.GetInstance().GetNetworkEntity()->GetRemotePort() << "> " << _pcPacketData << std::endl;

				//Retrieve off a message from the queue and process it
				_pServer->GetWorkQueue()->pop(_pcPacketData);
				_pServer->ProcessData(_pcPacketData);
			}
		}
	}
}

void CNetworkMgr::SetAsServer()
{
	_eNetworkEntityType = SERVER;
}

void CNetworkMgr::SetAsClient()
{
	_eNetworkEntityType = CLIENT;
}
