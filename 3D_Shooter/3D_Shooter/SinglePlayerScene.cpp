/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SinglePlayerScene.cpp
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Include 
#include "SinglePlayerScene.h"

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

CSinglePlayerScene::CSinglePlayerScene() :
	m_player(nullptr),
	EnemeyTemp(nullptr)
{}


CSinglePlayerScene::~CSinglePlayerScene()
{
	std::cout << "Single Player Game Scene Deleted... \n";
}

void CSinglePlayerScene::InitialiseScene(ESCENES _eSceneNum)
{
	//==========================================
	std::cout << "Game Initializing... \n";
	//==========================================

	m_pScore = new CTextLabel("Arial", "Score: 0", glm::vec2(1000.0f, 700.0f));
	m_pLife = new CTextLabel("Arial", "Life: 0", glm::vec2(0.0f, 700.0f));

	m_MainCamera = new CCamera();
	m_MainCamera->SetCameraPosition({ 0.0f, 45.0f, 65.0f });

	// Load in the cube map
	m_cCubeMap = cMeshMgr->GetCubeMap(GAMECUBEMAP);

	// Load in the game objects
	CGameObject* player = new CPlayer(cModelMgr->GetMesh(TANK), cAssetMgr->GetProgramID("ModelBlinnPhong"));
	Instantiate(player, glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << "Loaded GameObject: Player" << std::endl;
	m_player = player;

	CGameObject* platform = new CGameObject(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("STONE"),
		cAssetMgr->GetProgramID("BlinnPhong"));
	Instantiate(platform, glm::vec3(0.0f, -0.1f, 0.0f), glm::vec3(40.0f, 0.1f, 40.0f));
	std::cout << "Loaded GameObject: Platform" << std::endl;

	t1 = std::chrono::high_resolution_clock::now();
	tPowerUp1 = std::chrono::high_resolution_clock::now();
	//==========================================
	std::cout << "Initializing Done... \n";
	//==========================================
}

void CSinglePlayerScene::RenderScene()
{
	m_cCubeMap->Render(m_MainCamera);

	m_pScore->RenderTextLabel();
	m_pLife->RenderTextLabel();

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_MainCamera);
	}
	for (unsigned int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->RenderTextLabel();
	}
}

void CSinglePlayerScene::UpdateScene()
{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
	auto durationPowerUp = std::chrono::duration_cast<std::chrono::seconds>(tPowerUp2 - tPowerUp1);

	std::ostringstream iScore;
	iScore << "Score: " << m_GameScore;
	m_pScore->SetText(iScore.str());

	CPlayer* other = dynamic_cast<CPlayer*>(m_player);
	std::ostringstream iLife;
	iLife << "Life: " << other->GetHealth();
	m_pLife->SetText(iLife.str());

	//////////////Timer for enemey spawning/////////////////////////
	if (duration >= std::chrono::seconds(3))
	{
		for (int i = 0; i < 3; i++)
		{
			int WhichEnemy = rand() % 7;
			m_AiSwitch = rand() % 7;

			switch (m_AiSwitch)
			{
				//SEEK
			case 0:
			{
				CGameObject* Enemey = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("BOX"), cAssetMgr->GetProgramID("BlinnPhong"), SEEK, m_player);
				Instantiate(Enemey, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				break;
			}
			//FLEE
			case 1:
			{
				CGameObject* Enemey2 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("Bullet"), cAssetMgr->GetProgramID("BlinnPhong"), FLEE, m_player);
				Instantiate(Enemey2, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				break;
			}
			//PURSUE
			case 2:
			{
				CGameObject* Enemey2 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"), PURSUE, m_player);
				Instantiate(Enemey2, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				break;
			}
			//WANDER
			case 3:
			{
				CGameObject* Enemey2 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("Bullet"), cAssetMgr->GetProgramID("BlinnPhong"), WANDER, m_player);
				Instantiate(Enemey2, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				break;
			}
			//LEADERFOLLOW
			case 4:
			{

				if (b_isfirst == false)
				{
					CGameObject* Enemey2 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("STONE"), cAssetMgr->GetProgramID("BlinnPhong"), SEEK, m_player);
					Instantiate(Enemey2, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
					EnemeyTemp = Enemey2;
					b_isfirst = true;
				}
				else
				{
					CGameObject* Enemey = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("STONE"), cAssetMgr->GetProgramID("BlinnPhong"), SEEK, EnemeyTemp);
					Instantiate(Enemey, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				}

				break;
			}
			//ARRIVE
			case 5:
			{
				//for (int i = 0; i < 3; i++)
				//{
				CGameObject* Enemey3 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"), FLOCK, m_player);
				Instantiate(Enemey3, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));
				//}
				break;
			}

			default:
				break;
			}
		}

		t1 = std::chrono::high_resolution_clock::now();
	}
	//////////////Timer for PowerUp/////////////////////////
	if (durationPowerUp >= std::chrono::seconds(10))
	{
		int WhichPowerUp = rand() % 3;
		switch (WhichPowerUp)
		{
			//MOVESPD Powerup
		case 0:
		{
			CGameObject* powerUp = new CPowerUps(MOVESPD);
			Instantiate(powerUp, glm::vec3(-19 + rand() % (30), 1.0f, -19 + rand() % (30)));
			tPowerUp1 = std::chrono::high_resolution_clock::now();
			break;
		}
		//HEALTH Powerup
		case 1:
		{
			CGameObject* powerUp = new CPowerUps(HEAL);
			Instantiate(powerUp, glm::vec3(-19 + rand() % (30), 1.0f, -19 + rand() % (30)));
			tPowerUp1 = std::chrono::high_resolution_clock::now();
			break;
		}
		//SCORE Powerup
		case 2:
		{
			CGameObject* powerUp = new CPowerUps(SCORE);
			Instantiate(powerUp, glm::vec3(-19 + rand() % (30), 1.0f, -19 + rand() % (30)));
			tPowerUp1 = std::chrono::high_resolution_clock::now();
			break;
		}

		default: break;
		}

	}

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

	t2 = std::chrono::high_resolution_clock::now();
	tPowerUp2 = std::chrono::high_resolution_clock::now();
}

void CSinglePlayerScene::AddScore(int _point)
{
	m_GameScore += _point;
}

void CSinglePlayerScene::ChangeSwitch(int _int)
{
	m_AiSwitch = _int;
}
