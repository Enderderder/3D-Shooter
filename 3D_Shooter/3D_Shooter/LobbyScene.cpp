/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : LobbyScene.cpp
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Incldue 
#include "LobbyScene.h"

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
static CInput* cInputMgr =	CInput::GetInstance();

CLobbyScene::CLobbyScene()
{}

CLobbyScene::~CLobbyScene()
{
	std::cout << "Lobby Scene Deleted... \n";
}

void CLobbyScene::InitialiseScene(ESCENES _eSceneNum)
{
	m_MainCamera = new CCamera();

	m_cCubeMap = cMeshMgr->GetCubeMap(MENUCUBEMAP);

	m_tStartGame = std::make_shared<CTextLabel>("Arial", "Start Game", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 600));
	m_vTextLabel.push_back(m_tStartGame);

	m_tMainMenu = std::make_shared<CTextLabel>("Arial", "Main Menu", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 700));
	m_vTextLabel.push_back(m_tMainMenu);

	ChangeSelection(StartGame);

	/*TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 100));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 200));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 300));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 400));
	m_pText.push_back(TextTemp);*/
}

void CLobbyScene::RenderScene()
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

void CLobbyScene::UpdateScene()
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
		currVecSize = m_vGameObj.size(); // Revalidate the number of item inside the vector
	}

	CheckCollision();

	MenuControl();
}

void CLobbyScene::MenuControl()
{
	// When user choose to select up
	if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS 
		&& m_LobbyTracker == LobbyMainMenu)
	{
		cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		ChangeSelection(StartGame);
	}

	// When user choose to select down
	if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS 
		&& m_LobbyTracker == StartGame)
	{
		cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		ChangeSelection(LobbyMainMenu);
	}

	// When user press space to select
	if (cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;

		// Base on the current selection
		switch (m_LobbyTracker)
		{
		case StartGame:
		{
			if (cNetworkMgr->GetEntityType() == EEntityType::SERVER)
			{
				  
			}

			break;
		}
		case LobbyMainMenu:
		{
			cSceneMgr->SwapScene(MAINMENU);
			break;
		}
		default: break;
		}
	}
}

void CLobbyScene::ChangeSelection(LOBBYBUTTON _selection)
{
	m_LobbyTracker = _selection;

	switch (_selection)
	{
	case StartGame:
	{
		m_tStartGame->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
		m_tMainMenu->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		break;
	}
	case LobbyMainMenu:
	{
		m_tStartGame->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_tMainMenu->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
		break;
	}
	default: break;
	}
}