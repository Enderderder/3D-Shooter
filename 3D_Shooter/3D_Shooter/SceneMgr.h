/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SceneMgr.h
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef _SCENEMGR_H
#define _SCENEMGR_H

// Library Include
#include <vector>

// Local Include
#include "Scene.h"

// Enum Declare
enum ESCENES
{
	MAINMENU = 0,
	GAME,
	MULTIPLAYER,
	GAMEOVER
};

class CSceneMgr
{
public:
	// Singleton Methods
	static CSceneMgr* GetInstance();
	static void DestroyObject();

	// Member Functions
	void InitializeSceneMgr();
	void RenderCurrentScene();
	void UpdateCurrentScene();
	void SwapScene(ESCENES);
	CScene* GetCurrentScene() const;
	ESCENES GetCurrentSceneEnum() const;
	

private:
	// Make singleton by set the constructor inside private
	CSceneMgr();
	~CSceneMgr();

	// Make this class non-copyable
	CSceneMgr(const CSceneMgr& _kr) = delete;
	CSceneMgr& operator= (const CSceneMgr& _kr) = delete;

protected:
	// Singleton Object
	static CSceneMgr* s_pSceneMgr;

private:
	// Member Variables
	std::vector<CScene*> m_vScenes; // Scene Container

	ESCENES m_eCurrentScene; // Current scene thats displaying and updating
};

#endif // !_SCENEMGR_H