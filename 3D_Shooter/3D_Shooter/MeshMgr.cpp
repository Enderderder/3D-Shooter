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

// Static Variable
CMeshMgr* CMeshMgr::s_pMeshMgr = nullptr;

CMeshMgr & CMeshMgr::GetInstance()
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

void CMeshMgr::InitialiseMeshes()
{
	m_cCubeMesh = new CCubeMesh();
}

CMesh* CMeshMgr::GetCubeMesh() const
{
	return m_cCubeMesh;
}

CMeshMgr::CMeshMgr() {}


CMeshMgr::~CMeshMgr()
{
	
}
