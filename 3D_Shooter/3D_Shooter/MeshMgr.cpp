//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : MeshMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include 
#include "MeshMgr.h"

// Local Include
#include "CubeMesh.h"
#include "ShpereMesh.h"
#include "CubeMap.h"
#include "Utility.h"

// Static Variable
CMeshMgr* CMeshMgr::s_pMeshMgr = nullptr;

CMeshMgr* CMeshMgr::GetInstance()
{
	if (s_pMeshMgr == nullptr)
	{
		s_pMeshMgr = new CMeshMgr();
	}

	return s_pMeshMgr;
}

void CMeshMgr::DestroyInstance()
{
	delete s_pMeshMgr;
	s_pMeshMgr = nullptr;
}

void CMeshMgr::InitializeMeshes()
{
	// Load in the cube map
	std::vector<std::string> MenuCubeMapPaths = {
		"posx.jpg",
		"negx.jpg",
		"posy.jpg",
		"negy.jpg",
		"posz.jpg",
		"negz.jpg"
	};
	m_MenuCubeMap = new CCubeMap(MenuCubeMapPaths);
	std::cout << "Menu Cube Map Loaded. \n";

	std::vector<std::string> GameCubeMapPaths = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"back.jpg",
		"front.jpg"
	};
	m_GameCubemap = new CCubeMap(GameCubeMapPaths);
	std::cout << "Game Cube Map Loaded. \n";

	m_cCubeMesh = new CCubeMesh();
	m_cSphereMesh = new CShpereMesh();


	std::cout << "Mesh Loaded. \n";
}

CMesh * CMeshMgr::GetMesh(EMESH _eMesh) const
{
	switch (_eMesh)
	{
	case CUBE:
		return m_cCubeMesh;
		break;

	case SPHERE:
		return m_cSphereMesh;
		break;

	default:
		std::cout << "Cannot Grab Seleted Mesh. \n";
		return nullptr;
		break;
	}
}

CCubeMap* CMeshMgr::GetCubeMap(EMESH _eMesh) const
{
	switch (_eMesh)
	{
	case MENUCUBEMAP:
		return m_MenuCubeMap;
		break;

	case GAMECUBEMAP:
		return m_GameCubemap;
		break;

	default:
		std::cout << "Cannot Grab Seleted Cube Map. \n";
		return nullptr;
		break;
	}
}

CMeshMgr::CMeshMgr() {}

CMeshMgr::~CMeshMgr()
{
	// Clean up the member variables

	delete m_cCubeMesh;
	m_cCubeMesh = nullptr;

	delete m_cSphereMesh;
	m_cSphereMesh = nullptr;

	delete m_MenuCubeMap;
	m_MenuCubeMap = nullptr;

	delete m_GameCubemap;
	m_GameCubemap = nullptr;
}
