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

		m_cCam->SetCameraPosition({ 0.0f, 45.0f, 65.0f });

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


		break;
	}

	case MULTIPLAYER:
	{
		//==========================================
		std::cout << "Multiplayer Initializing... \n";
		//==========================================

		

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

		break;
	}

	case MAINMENU:
	{

		//==========================================
		std::cout << "Menu Initializing... \n";
		//==========================================

		m_cCubeMap = cMeshMgr->GetCubeMap(MENUCUBEMAP);

		TextTemp = new CTextLabel("Arial", "Play", glm::vec2(util::SCR_WIDTH/2, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Multiplayer", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Exit", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 200));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Space to Enter", glm::vec2(util::SCR_WIDTH / 8, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		//==========================================
		std::cout << "Initializing Done... \n";
		//==========================================

		break;
	}

	case MULTIPLAYERMENU:
	{
		m_cCubeMap = cMeshMgr->GetCubeMap(MENUCUBEMAP);

		TextTemp = new CTextLabel("Arial", "Host Game", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Join Game", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Main Menu", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 200));
		m_pText.push_back(TextTemp);

		break;
	}

	case LOBBY:
	{
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

		break;
	}

	case GAMEOVER:
	{
		m_cCubeMap = cMeshMgr->GetCubeMap(GAMECUBEMAP);

		TextTemp = new CTextLabel("Arial", "Restart", glm::vec2(util::SCR_WIDTH / 2- 200, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Return to Main Menu", glm::vec2(util::SCR_WIDTH / 2 - 200, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		TextTemp = new CTextLabel("Arial", "Space to Enter", glm::vec2(util::SCR_WIDTH / 8, util::SCR_HEIGHT / 2));
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
		m_pScore->RenderTextLabel();
		m_pLife->RenderTextLabel();
	}
	

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_cCam);
	}
	for (unsigned int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->RenderTextLabel();
	}
}

void CScene::ChangeSwitch(int _int)
{
	m_AiSwitch = _int;
}

void CScene::UpdateScene()
{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
	auto durationPowerUp = std::chrono::duration_cast<std::chrono::seconds>(tPowerUp2 - tPowerUp1);
	
	if (CSceneMgr::GetInstance()->GetCurrentSceneEnum() == GAME)
	{
		std::ostringstream iScore;
		iScore << "Score: " << m_GameScore;
		m_pScore->SetText(iScore.str());

		CPlayer* other = dynamic_cast<CPlayer*>(m_player);
		std::ostringstream iLife;
		iLife << "Life: " << other->GetHealth();
		m_pLife->SetText(iLife.str());

		if (other->GetHealth() <= 0)
		{
			//CSceneMgr::GetInstance()->SwapScene(GAMEOVER);
			//return;
		}

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
	}

	//m_cCam->UpdateCamera();

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

std::vector<CGameObject*> CScene::GetObjectVec() const
{
	return m_vGameObj;
}
