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
#include "Player.h"
#include "PowerUps.h"
#include "AssetMgr.h"
#include "MeshMgr.h"
#include "ModelMgr.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Camera.h"
#include "CAIMgr.h"
#include "CubeMap.h"
#include "TextLabel.h"

// Manager Pointer
static CAssetMgr* cAssetMgr = CAssetMgr::GetInstance();
static CModelMgr* cModelMgr = CModelMgr::GetInstance();
static CMeshMgr* cMeshMgr = CMeshMgr::GetInstance();

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

	/*TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 100));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 200));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 300));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Not Connected", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 400));
	m_pText.push_back(TextTemp);*/


	TextTemp = new CTextLabel("Arial", "Start Game", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 600));
	m_pText.push_back(TextTemp);

	TextTemp = new CTextLabel("Arial", "Main Menu", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT - 700));
	m_pText.push_back(TextTemp);
}

void CLobbyScene::RenderScene()
{
	m_cCubeMap->Render(m_MainCamera);

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_MainCamera);
	}
	for (unsigned int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->RenderTextLabel();
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
}

void CLobbyScene::MenuControl()
{

}
