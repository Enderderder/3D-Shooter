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
#include "MeshMgr.h"
#include "ModelMgr.h"
#include "Camera.h"
#include "CAIMgr.h"

// Global Variables
GLuint diffuseProgram;
GLuint texture;
TextLabel* TextTemp;


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
		static ShaderLoader shaderLoader;
		diffuseProgram = shaderLoader.CreateProgram("Shaders/BlinnPhong.vs", "Shaders/BlinnPhong.fs");
		GLuint dp = shaderLoader.CreateProgram("Shaders/ModelShader.vs", "Shaders/ModelShader.fs");

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;
		std::cout << "Filename Address: Resources/Textures/TITANFALL.jpg" << std::endl;

		unsigned char* image = SOIL_load_image(
			"Resources/Textures/TITANFALL.jpg",	// File path / Name
			&width,								// Output for the image width
			&height,							// Output for the image height
			0,									// Output for number of channels
			SOIL_LOAD_RGBA);					// Load RGB values only

		glTexImage2D(
			GL_TEXTURE_2D,		// Type of texture
			0,					// Mipmap level, 0 for base
			GL_RGBA,			// Number of color components in texture
			width,				// Width of the texture
			height,				// Height of the texture
			0,					// This value must be 0
			GL_RGBA,			// Format for the pixel data
			GL_UNSIGNED_BYTE,	// Data type for the pixel data
			image);				// Pointer to image data in memory

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

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
		CGameObject* player = new CPlayer(CModelMgr::GetInstance().GetMesh(TANK), dp);
		Instantiate(player, glm::vec3(0.0f, 1.0f, 0.0f));
		std::cout << "Loaded GameObject: Player" << std::endl;
		m_player = player;

		CGameObject* Enemey = new CAIMgr(CMeshMgr::GetInstance().GetMesh(CUBE), texture, diffuseProgram, SEEK, player);
		Instantiate(Enemey, glm::vec3(15.0f, 1.0f, 15.0f));

		std::cout << "Loaded GameObject: Player" << std::endl;

		CGameObject* platform = new CGameObject(CMeshMgr::GetInstance().GetMesh(CUBE), texture, diffuseProgram);
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

		TextTemp = new TextLabel("Press Esc to Exit", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH / 2, util::SCR_HEIGHT / 2 - 20));
		m_pText.push_back(TextTemp);

		TextTemp = new TextLabel("Press F for Fullscreen", "Resources/fonts/arial.ttf", glm::vec2(util::SCR_WIDTH, util::SCR_HEIGHT));
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
