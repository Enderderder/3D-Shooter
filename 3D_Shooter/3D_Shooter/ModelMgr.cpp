//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : ModelMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "ModelMgr.h"

// Local Include
#include "Utility.h"
#include "Model.h"
#include "ShaderLoader.h"

// Static Variable
CModelMgr* CModelMgr::s_pModelMgr = nullptr;

CModelMgr* CModelMgr::GetInstance()
{
	if (s_pModelMgr == nullptr)
	{
		s_pModelMgr = new CModelMgr();
	}

	return s_pModelMgr;
}

void CModelMgr::DestroyInstance()
{
	delete s_pModelMgr;
	s_pModelMgr = nullptr;
}

void CModelMgr::InitializeModels()
{
	m_cTankModel = new CModel("Resources/Models/Tank/Tank.obj");
}

CModel* CModelMgr::GetMesh(EMODEL _eModel) const
{
	switch (_eModel)
	{
	case TANK:
		return m_cTankModel;
		break;

	default:
		std::cout << "Unable to grab model. \n";
		break;
	}
	return nullptr;
}

CModelMgr::CModelMgr()
{}


CModelMgr::~CModelMgr()
{}
