//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : SceneMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob (Last Name?)
// Mail         : richard.wul7481@mediadesign.school.nz (Email?)
//

// This Include
#include "SceneMgr.h"

// Local Include
#include "Utility.h"

// Static Variable
CSceneMgr* CSceneMgr::s_pSceneMgr = nullptr;

CSceneMgr & CSceneMgr::GetInstance()
{
	if (s_pSceneMgr == nullptr)
	{
		s_pSceneMgr = new CSceneMgr();
	}

	return *s_pSceneMgr;
}

void CSceneMgr::DestroyInstance()
{
	delete s_pSceneMgr;
	s_pSceneMgr = nullptr;
}

void CSceneMgr::Initialise()
{
	m_CurrentScene = MAINMENU;

}

void CSceneMgr::RenderCurrentScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_vScenes[m_CurrentScene]->RenderScene();
}

void CSceneMgr::UpdateCurrentScene()
{
	m_vScenes[m_CurrentScene]->UpdateScene();
}

void CSceneMgr::SwapScene(ESCENES _eSceneNum)
{
	// Reset the current scene
	delete m_vScenes[m_CurrentScene];
	m_vScenes[m_CurrentScene] = new CScene(m_CurrentScene);

	// Jump to another scene and initialise it
	m_CurrentScene = _eSceneNum;
	m_vScenes[m_CurrentScene]->InitialiseScene();
}

CSceneMgr::CSceneMgr()
{}

CSceneMgr::~CSceneMgr()
{}
