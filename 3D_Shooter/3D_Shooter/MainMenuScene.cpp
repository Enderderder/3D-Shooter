//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : MainMenuScene.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "MainMenuScene.h"

// Local Include
#include "Utility.h"

#include "GameObject.h"
#include "AssetMgr.h"
#include "MeshMgr.h"
#include "ModelMgr.h"
#include "SceneMgr.h"
#include "CNetworkMgr.h"
#include "network.h"
#include "Input.h"
#include "Camera.h"
#include "CubeMap.h"
#include "TextLabel.h"

// Manager Pointer
static CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();
static CNetworkMgr* cNetworkMgr = CNetworkMgr::GetInstance();
static CAssetMgr* cAssetMgr = CAssetMgr::GetInstance();
static CModelMgr* cModelMgr = CModelMgr::GetInstance();
static CMeshMgr* cMeshMgr = CMeshMgr::GetInstance();
static CInput* cInputMgr = CInput::GetInstance();

CMainMenuScene::CMainMenuScene()
{}

CMainMenuScene::~CMainMenuScene()
{
	std::cout << "Main Menu Scene Deleted... \n";
}

void CMainMenuScene::InitialiseScene(ESCENES _eSceneNum)
{
	m_MainCamera = new CCamera();

	m_cCubeMap = cMeshMgr->GetCubeMap(MENUCUBEMAP);

	m_tSinglePlayer = std::make_shared<CTextLabel>("Arial", "Play", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 600));
	m_vTextLabel.push_back(m_tSinglePlayer);

	m_tMultiPlayer = std::make_shared<CTextLabel>("Arial", "Multiplayer", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 700));
	m_vTextLabel.push_back(m_tMultiPlayer);

	m_tExitGame = std::make_shared<CTextLabel>("Arial", "Exit", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 700));
	m_vTextLabel.push_back(m_tExitGame);
}

void CMainMenuScene::RenderScene()
{
	m_cCubeMap->Render(m_MainCamera);

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_MainCamera);
	}

	for (auto text : m_vTextLabel)
	{
		text->RenderTextLabel();
	}
}

void CMainMenuScene::UpdateScene()
{
	m_MainCamera->UpdateCamera();

	// Delete the object that should be deleted fron last frame
	for (auto obj : m_vGameObj)
	{
		if (obj->ShouldDestroyed()) { DestroyObject(obj); }
	}

	// Get each Object in the Scene and do their own Update Function
	size_t currVecSize = m_vGameObj.size();
	for (size_t index = 0; index < currVecSize; ++index)
	{
		m_vGameObj[index]->UpdateGameObeject();
		currVecSize = m_vGameObj.size(); // Re validate the number of item inside the vector
	}

	CheckCollision();

	MenuControl();
}

void CMainMenuScene::MenuControl()
{
	// When user choose to select up
	if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;

		switch (m_MainMenuTracker)
		{
		case Exit:
		{
			ChangeSelection(Multiplayer);
			break;
		}
		case Multiplayer:
		{
			ChangeSelection(Play);
			break;
		}

		default: break;
		}
	}

	// When user choose to select down
	if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		
		switch (m_MainMenuTracker)
		{
		case Play:
		{
			ChangeSelection(Multiplayer);
			break;
		}
		case Multiplayer:
		{
			ChangeSelection(Exit);
			break;
		}

		default: break;
		}
	}

	// When user press space to select
	if (cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;

		// Base on the current selection
		switch (m_MainMenuTracker)
		{
		case Play:
		{
			cSceneMgr->SwapScene(GAME);
			break;
		}
		case Multiplayer:
		{
			cSceneMgr->SwapScene(MULTIPLAYERMENU);
			break;
		}
		case Exit:
		{
			glutLeaveMainLoop();
			break;
		}

		default: break;
		}
	}
}

void CMainMenuScene::ChangeSelection(MAINMENUBUTTON _selection)
{
	m_MainMenuTracker = _selection;

	switch (_selection)
	{
	case Play:
	{
		m_tSinglePlayer->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
		m_tMultiPlayer->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_tExitGame->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		break;
	}
	case Multiplayer:
	{
		m_tSinglePlayer->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_tMultiPlayer->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
		m_tExitGame->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		break;
	}
	case Exit:
	{
		m_tSinglePlayer->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_tMultiPlayer->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_tExitGame->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
		break;
	}

	default: break;
	}
}
