/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CNetworkMgr.h
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#pragma once

#include "Utility.h"

// Forward Declare
enum EEntityType;

class CNetworkMgr
{
public:
	CNetworkMgr();
	~CNetworkMgr();

	void StartNetwork();
	void SetAsServer();
	void SetAsClient();
	void ClientMainLoop();
	void ServerMainLoop();



private:

	EEntityType _eNetworkEntityType;  //= SERVER;//defualt it is a server

	std::thread m_ClientReceiveThread;
	std::thread m_ServerReceiveThread;

	//_rNetwork
	//_pClient
	//_InputBuffer
};

