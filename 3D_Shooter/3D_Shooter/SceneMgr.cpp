//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : 
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
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
		m_eCurrentScene = MAINMENU;
		m_vScenes.push_back(new CScene);
	
}

void CSceneMgr::RenderCurrentScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_vScenes[m_eCurrentScene]->RenderScene();
}

void CSceneMgr::UpdateCurrentScene()
{
	m_vScenes[m_eCurrentScene]->UpdateScene();
}

void CSceneMgr::SwapScene(ESCENES _eSceneNum)
{
	// Reset the current scene
	delete m_vScenes[m_eCurrentScene];
	m_vScenes[m_eCurrentScene] = new CScene(m_eCurrentScene);

	// Jump to another scene and initialise it
	m_eCurrentScene = _eSceneNum;
	m_vScenes[m_eCurrentScene]->InitialiseScene();
}

CSceneMgr::CSceneMgr()
{}

CSceneMgr::~CSceneMgr()
{}
