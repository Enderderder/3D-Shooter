//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Scene.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "Scene.h"

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

// Global Variables
TextLabel* TextTemp;

// Manager Pointer
static CAssetMgr* cAssetMgr = CAssetMgr::GetInstance();
static CModelMgr* cModelMgr = CModelMgr::GetInstance();
static CMeshMgr* cMeshMgr = CMeshMgr::GetInstance();

CScene::CScene(ESCENES _eSceneNum)
{
	m_vGameObj.resize(0);
	m_pText.resize(0);

	m_cCam = nullptr;
	m_cCubeMap = nullptr;
	m_player = nullptr;
}

CScene::~CScene()
{
	std::cout << "Cleaning Scene... \n";
	// Clean up the memory allocated variables inside the class

	// ========================================================
	delete m_cCam;
	m_cCubeMap = nullptr;

	for (auto obj : m_vGameObj)
	{
		delete obj;
	}
	m_vGameObj.clear();

	for (auto text : m_pText)
	{
		delete text;
	}
	m_pText.clear();

	// ========================================================
	std::cout << "Cleaning Done... \n";
}

void CScene::InitialiseScene(ESCENES _eSceneNum)
{
	m_cCam = new CCamera();

	switch (_eSceneNum)
	{
	case GAME:
	{
		//==========================================
		std::cout << "Game Initializing... \n";
		//==========================================

		// Load in the cube map
		m_cCubeMap = cMeshMgr->GetCubeMap(GAMECUBEMAP);
		
		// Load in the game objects
		CGameObject* player = new CPlayer(cModelMgr->GetMesh(TANK), cAssetMgr->GetProgramID("ModelBlinnPhong"));
		Instantiate(player, glm::vec3(0.0f, 0.0f, 0.0f));
		std::cout << "Loaded GameObject: Player" << std::endl;
		m_player = player;

		CGameObject* Enemey = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"), FLEE, player);
		Instantiate(Enemey, glm::vec3(12.0f, 0.0f, 12.0f));

		std::cout << "Loaded GameObject: Enemy" << std::endl;

		CGameObject* platform = new CGameObject(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("STONE"), cAssetMgr->GetProgramID("BlinnPhong"));
		Instantiate(platform, glm::vec3(0.0f, -0.1f, 0.0f), glm::vec3(20.0f, 0.1f, 20.0f));
		std::cout << "Loaded GameObject: Platform" << std::endl;

		CGameObject* powerUp = new CPowerUps(MOVESPD);
		Instantiate(powerUp, glm::vec3(5.0f, 1.0f, 5.0f));

		t1 = std::chrono::high_resolution_clock::now();
		tPowerUp1 = std::chrono::high_resolution_clock::now();
		//==========================================
		std::cout << "Initializing Done... \n";
		//==========================================


		break;
	}

	case MAINMENU:
	{

		//==========================================
		std::cout << "Menu Initializing... \n";
		//==========================================

		m_cCubeMap = cMeshMgr->GetCubeMap(MENUCUBEMAP);

		TextTemp = new TextLabel("Press P to Play", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH/2, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press Esc to Exit", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press F for Fullscreen", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 200));
		m_pText.push_back(TextTemp);

		//==========================================
		std::cout << "Initializing Done... \n";
		//==========================================

		break;
	}

	case GAMEOVER:
	{
		m_cCubeMap = cMeshMgr->GetCubeMap(GAMECUBEMAP);

		TextTemp = new TextLabel("Press r to Restart", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2- 200, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press e to Return to the Main Menu", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2 - 200, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		break;
	}

	default: break;
	}
}

void CScene::RenderScene()
{
	m_cCubeMap->Render(m_cCam);

	if (CSceneMgr::GetInstance()->GetCurrentSceneEnum() == GAME)
	{
		m_pScore->Render();
		m_pLife->Render();
	}
	

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_cCam);
	}
	for (int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->Render();
	}
}

void CScene::UpdateScene()
{
	/*Debbug*************************************************************************/
	/*if (CInput::GetInstance()->g_cKeyState[(unsigned int)'h'] == INPUT_FIRST_PRESS)
	{
		std::cout << "Loading back to main menu. \n";
		CSceneMgr::GetInstance()->SwapScene(MAINMENU);
		return;
	}*/
	/*********************************************************************************/
	
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
	auto durationPowerUp = std::chrono::duration_cast<std::chrono::seconds>(tPowerUp2 - tPowerUp1);
	
	if (CSceneMgr::GetInstance()->GetCurrentSceneEnum() == GAME)
	{
		std::ostringstream iScore;
		iScore << "Score: " << m_GameScore;
		m_pScore->SetText(iScore.str());

		CPlayer* other = dynamic_cast<CPlayer*>(m_player);
		std::ostringstream iLife;
		iLife << "Life: " << other->GetLife();
		m_pLife->SetText(iLife.str());

		if (other->GetLife() <= 0)
		{
			CSceneMgr::GetInstance()->SwapScene(GAMEOVER);
			return;
		}

		//////////////Timer for enemey spawning/////////////////////////
		if (duration >= std::chrono::seconds(3))
		{
			CGameObject* Enemey = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("BOX"), cAssetMgr->GetProgramID("BlinnPhong"), SEEK, m_player);
			Instantiate(Enemey, glm::vec3(-19 + rand()%  (30), 0.0f, -19 + rand() % (30)));

			CGameObject* Enemey2 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("Bullet"), cAssetMgr->GetProgramID("BlinnPhong"), FLEE, m_player);
			Instantiate(Enemey2, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));

			CGameObject* Enemey3 = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"), WANDER, m_player);
			Instantiate(Enemey3, glm::vec3(-19 + rand() % (30), 0.0f, -19 + rand() % (30)));

			t1 = std::chrono::high_resolution_clock::now();
		}
		//////////////Timer for PowerUp/////////////////////////
		if (durationPowerUp >= std::chrono::seconds(10))
		{
			CGameObject* powerUp = new CPowerUps(MOVESPD);
			Instantiate(powerUp, glm::vec3(-19 + rand() % (30), 1.0f, -19 + rand() % (30)));
			tPowerUp1 = std::chrono::high_resolution_clock::now();
		}
	}

	

	
	m_cCam->UpdateCamera();

	// Delete the object that should be deleted fron last frame
	for (auto obj : m_vGameObj)
	{
		if (obj->ShouldDestroyed()) { DestroyObject(obj); }
	}

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

void CScene::CheckCollision()
{
	size_t currVecSize = m_vGameObj.size();
	for (size_t index = 0; index < currVecSize; ++index)
	{
		if (m_vGameObj[index]->HasCollider()) // Check if object itself has a collider
		{
			// Get the collistion detail of the object
			float selfCollider = m_vGameObj[index]->GetCollisionRad();
			glm::vec3 selfPos = m_vGameObj[index]->GetPosition();

			// Check with all the rest of the other objects
			for (size_t i = index + 1; i < currVecSize; ++i)
			{
				if (m_vGameObj[i]->HasCollider())
				{
					// Get the other objects' collision detail
					float otherCollider = m_vGameObj[i]->GetCollisionRad();
					glm::vec3 otherPos = m_vGameObj[i]->GetPosition();

					float distance = glm::distance(selfPos, otherPos);
					if (distance <= (selfCollider + otherCollider))
					{
						m_vGameObj[index]->OnCollision(m_vGameObj[i]);
						m_vGameObj[i]->OnCollision(m_vGameObj[index]);
					}
				}
			}
		}
		


		currVecSize = m_vGameObj.size(); // Revalidate the number of item inside the vector
	}
}

void CScene::Instantiate(CGameObject * _gameobj)
{
	m_vGameObj.push_back(_gameobj);
}

void CScene::Instantiate(CGameObject * _gameobj, glm::vec3 _pos)
{
	_gameobj->SetPosition(_pos);
	m_vGameObj.push_back(_gameobj);
}

void CScene::Instantiate(CGameObject * _gameobj, glm::vec3 _pos, glm::vec3 _scale)
{
	_gameobj->SetPosition(_pos);
	_gameobj->SetScale(_scale);
	m_vGameObj.push_back(_gameobj);
}

void CScene::Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation)
{
	_gameobj->SetPosition(_pos);
	_gameobj->SetScale(_scale);
	_gameobj->SetRotation(_rotation);
	m_vGameObj.push_back(_gameobj);
}

void CScene::DestroyObject(CGameObject* _gameobj)
{
	for (auto iter = m_vGameObj.begin(); iter != m_vGameObj.end(); ++iter)
	{
		if ((*iter) == _gameobj)
		{
			delete (*iter);
			m_vGameObj.erase(iter);
			break;
		}
	}
}

void CScene::AddScore(int _point)
{
	m_GameScore += _point;
}
