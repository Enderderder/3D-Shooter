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

#ifndef CNETWORKMGR_H
#define CNETWORKMGR_H

// Library Include
#include <thread>

// Forward Declare
enum EEntityType;
class CNetwork;

class CNetworkMgr
{
public:
	CNetworkMgr();
	~CNetworkMgr();

	void StartNetwork(EEntityType);
	void SetAsServer();
	void SetAsClient();
	EEntityType GetEntityType();
	void ClientMainLoop();
	void ServerMainLoop();

	bool IsNetOnline() const;

private:

	EEntityType _eNetworkEntityType;

	std::thread m_ClientReceiveThread;
	std::thread m_ServerReceiveThread;

};

#endif // !CNETWORKMGR_H