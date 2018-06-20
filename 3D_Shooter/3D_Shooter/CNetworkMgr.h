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
	// Singleton Methods
	static CNetworkMgr* GetInstance();
	static void DestroyInstance();

	// Member Functions
	void StartNetwork(EEntityType);
	void SetAsServer();
	void SetAsClient();
	EEntityType GetEntityType();
	void ClientMainLoop();
	void ServerMainLoop();

	bool IsNetOnline() const;

private:
	// Make singleton by set the constructor inside private
	CNetworkMgr();
	~CNetworkMgr();

	// Make this class non-copyable
	CNetworkMgr(const CNetworkMgr& _kr) = delete;
	CNetworkMgr& operator= (const CNetworkMgr& _kr) = delete;

protected:
	// Singleton Object
	static CNetworkMgr* s_pNetworkMgr;

private:
	// Member Variables

	EEntityType _eNetworkEntityType;

	std::thread m_ClientReceiveThread;
	std::thread m_ServerReceiveThread;
};

#endif // !CNETWORKMGR_H