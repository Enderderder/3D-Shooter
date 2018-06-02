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

// Local Include
#include "Scene.h"

// Global Include
#include "Utility.h"
#include "GameObject.h"
#include "MeshMgr.h"
#include "Camera.h"

// Global Variables
GLuint diffuseProgram;
GLuint texture;

CScene::CScene(ESCENES _eSceneNum)
{
	InitialiseScene(_eSceneNum);
}

CScene::~CScene()
{
	// Clean up the memory allocated variables inside the class

	delete m_cCam;
	delete m_cCubeMap;

	for (auto obj : m_vGameObj)
	{
		delete obj;
	}
}

void CScene::InitialiseScene(ESCENES _eSceneNum)
{
	m_cCam = new CCamera();

	switch (_eSceneNum)
	{
	case MAINMENU:
	{
		static ShaderLoader shaderLoader;
		diffuseProgram = shaderLoader.CreateProgram("Shaders/DiffuseLight.vs", "Shaders/DiffuseLight.fs");

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;
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


		std::vector<std::string> cubeMapPaths = {
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"back.jpg",
			"front.jpg"
		};
		//m_cCubeMap = new CCubeMap(cubeMapPaths);
		
		m_vGameObj.push_back(new CGameObject(CMeshMgr::GetInstance().GetCubeMesh(), &texture, &diffuseProgram));
		
		break;
	}


	default: break;
	}
}

void CScene::RenderScene()
{
	//m_cCubeMap->Render(m_cCam);

	for (auto obj : m_vGameObj)
	{
		obj->RenderObject(m_cCam);
	}


}

void CScene::UpdateScene()
{

}
