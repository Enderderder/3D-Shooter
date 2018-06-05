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
#include "Utility.h"

// Static Variable
CMeshMgr* CMeshMgr::s_pMeshMgr = nullptr;

CMeshMgr& CMeshMgr::GetInstance()
{
	if (s_pMeshMgr == nullptr)
	{
		s_pMeshMgr = new CMeshMgr();
	}

	return *s_pMeshMgr;
}

void CMeshMgr::DestroyInstance()
{
	delete s_pMeshMgr;
	s_pMeshMgr = nullptr;
}

void CMeshMgr::InitializeMeshes()
{
	m_cCubeMesh = new CCubeMesh();
	m_cSphereMesh = new CShpereMesh();
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

CMeshMgr::CMeshMgr() {}

CMeshMgr::~CMeshMgr()
{
	// Clean up the member variables

	delete m_cCubeMesh;
	m_cCubeMesh = nullptr;

	delete m_cSphereMesh;
	m_cSphereMesh = nullptr;
}
