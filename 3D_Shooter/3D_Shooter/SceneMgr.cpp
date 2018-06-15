/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SceneMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Include
#include "SceneMgr.h"

// Static Variable
CSceneMgr* CSceneMgr::s_pSceneMgr = nullptr;

CSceneMgr* CSceneMgr::GetInstance()
{
	if (s_pSceneMgr == nullptr)
	{
		s_pSceneMgr = new CSceneMgr();
	}

	return s_pSceneMgr;
}

void CSceneMgr::DestroyObject()
{
	delete s_pSceneMgr;
	s_pSceneMgr = nullptr;
}

void CSceneMgr::InitializeSceneMgr()
{
	m_vScenes.push_back(new CScene(MAINMENU));
	m_vScenes.push_back(new CScene(GAME));
	m_vScenes.push_back(new CScene(MULTIPLAYER));
	m_vScenes.push_back(new CScene(GAMEOVER));

	m_eCurrentScene = MAINMENU;
	m_vScenes[m_eCurrentScene]->InitialiseScene(m_eCurrentScene);
}

void CSceneMgr::RenderCurrentScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_vScenes[m_eCurrentScene]->RenderScene();
}

void CSceneMgr::UpdateCurrentScene()
{
	// Only Proccess the current running scene
	m_vScenes[m_eCurrentScene]->UpdateScene();
}

void CSceneMgr::SwapScene(ESCENES _eSceneNum)
{
	// Reset the current scene
	delete m_vScenes[m_eCurrentScene];
	m_vScenes[m_eCurrentScene] = new CScene(m_eCurrentScene);

	// Jump to another scene and initialise it
	m_eCurrentScene = _eSceneNum;
	m_vScenes[m_eCurrentScene]->InitialiseScene(m_eCurrentScene);
}

CScene * CSceneMgr::GetCurrentScene() const
{
	return m_vScenes[m_eCurrentScene];
}

ESCENES CSceneMgr::GetCurrentSceneEnum() const
{
	return m_eCurrentScene;
}

CSceneMgr::CSceneMgr()
{}

CSceneMgr::~CSceneMgr()
{
	for (auto scene : m_vScenes)
	{
		delete scene;
	}
	m_vScenes.clear();
}
