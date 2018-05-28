//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : SceneMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob (Last Name?)
// Mail         : richard.wul7481@mediadesign.school.nz (Email?)
//

#ifndef _SCENEMGR_H
#define _SCENEMGR_H

// Library Include
#include <vector>

// Local Include
#include "Scene.h"

// Forward Declaration
enum ESCENES;

class CSceneMgr
{
public:
	// Singleton Methods
	static CSceneMgr& GetInstance();
	static void DestroyInstance();

	// Member Function
	void Initialise();
	void RenderCurrentScene();
	void UpdateCurrentScene();
	void SwapScene(ESCENES _eSceneNum);

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
	// Member Variable
	std::vector<CScene*> m_vScenes; // Scene Container

	ESCENES m_CurrentScene; // Current scene thats displaying and updating
};

#endif // !_SCENEMGR_H