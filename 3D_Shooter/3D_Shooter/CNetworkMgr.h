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

};

