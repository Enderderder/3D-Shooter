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
#include "AssetMgr.h"
#include "MeshMgr.h"
#include "ModelMgr.h"
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
	InitialiseScene(_eSceneNum);
}

CScene::~CScene()
{
	// Clean up the memory allocated variables inside the class

	// ========================================================
	delete m_cCam;
	delete m_cCubeMap;

	for (auto obj : m_vGameObj)
	{
		delete obj;
	}
	m_vGameObj.clear();
	// ========================================================
}

void CScene::InitialiseScene(ESCENES _eSceneNum)
{
	m_cCam = new CCamera();

	switch (_eSceneNum)
	{
	case GAME:
	{
		m_pCurrentEnum = GAME;
		
		// Load in the cube map
		std::vector<std::string> cubeMapPaths = {
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"back.jpg",
			"front.jpg"
		};
		m_cCubeMap = new CCubeMap(cubeMapPaths);
		
		// Load in the game objects
		CGameObject* player = new CPlayer(cModelMgr->GetMesh(TANK), cAssetMgr->GetProgramID("ModelBlinnPhong"));
		Instantiate(player, glm::vec3(0.0f, 1.0f, 0.0f));
		std::cout << "Loaded GameObject: Player" << std::endl;
		m_player = player;

		CGameObject* Enemey = new CAIMgr(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"), SEEK, player);
		Instantiate(Enemey, glm::vec3(15.0f, 1.0f, 15.0f));

		std::cout << "Loaded GameObject: Enemy" << std::endl;

		CGameObject* platform = new CGameObject(cMeshMgr->GetMesh(CUBE), cAssetMgr->GetTextureID("TITANFALL"), cAssetMgr->GetProgramID("BlinnPhong"));
		Instantiate(platform, glm::vec3(0.0f, -0.1f, 0.0f), glm::vec3(20.0f, 0.1f, 20.0f));
		std::cout << "Loaded GameObject: Platform" << std::endl;


		break;
	}

	case MAINMENU:
	{
		m_pCurrentEnum = MAINMENU;
		static ShaderLoader shaderLoader;
		diffuseProgram = shaderLoader.CreateProgram("Shaders/BlinnPhong.vs", "Shaders/BlinnPhong.fs");
		GLuint dp = shaderLoader.CreateProgram("Shaders/ModelShader.vs", "Shaders/ModelShader.fs");

		// Load in the cube map
		std::vector<std::string> cubeMapPaths = {
			"posx.jpg",
			"negx.jpg",
			"posy.jpg",
			"negy.jpg",
			"posz.jpg",
			"negz.jpg"
		};
		m_cCubeMap = new CCubeMap(cubeMapPaths);

		TextTemp = new TextLabel("Press P to Play", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH/2, util::SCR_HEIGHT / 2));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press Esc to Exit", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 100));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press F for Fullscreen", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 200));
		m_pText.push_back(TextTemp);

		break;
	}

	case GAMEOVER:
	{
		m_pCurrentEnum = GAMEOVER;

		break;
	}

	default: break;
	}
}

ESCENES CScene::GetCurrentEnum()
{
	return(m_pCurrentEnum);
}

void CScene::RenderScene()
{
	m_cCubeMap->Render(m_cCam);

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
	m_cCam->UpdateCamera();

	size_t currVecSize = m_vGameObj.size();
	for (size_t index = 0; index < currVecSize; ++index)
	{
		m_vGameObj[index]->UpdateGameObeject();
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

void CScene::Instantiate(CGameObject * _gameobj, glm::vec3 _pos, float _rotate)
{
	_gameobj->SetPosition(_pos);
	_gameobj->SetRotation(_rotate);
	m_vGameObj.push_back(_gameobj);
}

void CScene::DestroyInstance(CGameObject* _gameobj)
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
