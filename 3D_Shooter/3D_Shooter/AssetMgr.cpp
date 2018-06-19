//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SceneMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "AssetMgr.h"

// Local Include
#include "Utility.h"
#include "ShaderLoader.h"
#include "TextLoader.h"

// Static Variable
CAssetMgr* CAssetMgr::s_pAssetMgr = nullptr;

CAssetMgr* CAssetMgr::GetInstance()
{
	if (s_pAssetMgr == nullptr)
	{
		s_pAssetMgr = new CAssetMgr();
	}

	return s_pAssetMgr;
}

void CAssetMgr::DestroyInstance()
{
	delete s_pAssetMgr;
	s_pAssetMgr = nullptr;
}

void CAssetMgr::InitializeAssets()
{
	// Initalize Program
	static ShaderLoader shaderLoader;
	m_programBlinnPhong = shaderLoader.CreateProgram("Shaders/BlinnPhong.vs", "Shaders/BlinnPhong.fs");
	m_programRimLight = shaderLoader.CreateProgram("Shaders/RimLight.vs", "Shaders/RimLight.fs");
	m_programReflectRim = shaderLoader.CreateProgram("Shaders/ReflectRim.vs", "Shaders/ReflectRim.fs");
	m_programModelBlinnPhong = shaderLoader.CreateProgram("Shaders/ModelShader.vs", "Shaders/ModelShader.fs");
	m_programText = shaderLoader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");

	// Initialize Texture
	BindTexture("Resources/Textures/TITANFALL.jpg", m_texTITANFALL);
	BindTexture("Resources/Textures/BulletTex.jpg", m_texBullet);
	BindTexture("Resources/Textures/Fallout Box.jpg", m_FalloutBox);
	BindTexture("Resources/Textures/Box.jpg", m_Box);
	BindTexture("Resources/Textures/Brick.jpg", m_Brick);
	BindTexture("Resources/Textures/Stone.jpg", m_Stone);

	// Initialize Font/Text
	m_textArial = new Text("Resources/fonts/arial.ttf");
}

GLuint CAssetMgr::GetTextureID(const char* _name) const
{
	if (_name == "TITANFALL")
	{
		return m_texTITANFALL;
	}
	else if (_name == "Bullet")
	{
		return m_texBullet;
	}
	else if (_name == "FALLOUTBOX")
	{
		return m_FalloutBox;
	}
	else if (_name == "BOX")
	{
		return m_Box;
	}
	else if (_name == "BRICK")
	{
		return m_Brick;
	}
	else if (_name == "STONE")
	{
		return m_Stone;
	}

	std::cout << "Fail to Grab " << _name << ", texture does not exist. \n";
	return NULL;
}

GLuint CAssetMgr::GetProgramID(const char* _name) const
{
	if (_name == "BlinnPhong")
	{
		return m_programBlinnPhong;
	}
	else if (_name == "RimLight")
	{
		return m_programRimLight;
	}
	else if (_name == "ModelBlinnPhong")
	{
		return m_programModelBlinnPhong;
	}
	else if (_name == "ReflectRim")
	{
		return m_programReflectRim;
	}
	else if (_name == "Text")
	{
		return m_programText;
	}

	std::cout << "Fail to Grab " << _name << ", program does not exist. \n";
	return NULL;
}

Text * CAssetMgr::GetTextID(const char* _fontName) const
{
	if (_fontName == "Arial")
	{
		return m_textArial;
	}

	std::cout << "Fail to Grab Text " << _fontName << ", program does not exist. \n";
	return nullptr;
}

void CAssetMgr::BindTexture(const char* _path, GLuint& _id)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	int width, height;
	std::cout << "Loading Texture: " << _path << "\n";

	unsigned char* image = SOIL_load_image(
		_path,				// File path / Name
		&width,				// Output for the image width
		&height,			// Output for the image height
		0,					// Output for number of channels
		SOIL_LOAD_RGBA);	// Load RGB values only

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
}

CAssetMgr::CAssetMgr()
{}


CAssetMgr::~CAssetMgr()
{
	// Delete all the Font/Text pointer
	delete m_textArial;
	m_textArial = nullptr;
}
