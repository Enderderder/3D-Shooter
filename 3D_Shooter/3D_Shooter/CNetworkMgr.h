#pragma once

#include "Utility.h"
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


	//_rNetwork
	//_pClient
	//_InputBuffer
};

