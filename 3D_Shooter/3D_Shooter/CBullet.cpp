//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Bullet.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "CBullet.h"

// Local Include
#include "SceneMgr.h"
#include "MeshMgr.h"
#include "AssetMgr.h"

// Manager Class Pointer
static CAssetMgr* cAssetMgr = CAssetMgr::GetInstance();
static CMeshMgr* cMeshMgr = CMeshMgr::GetInstance();

CBullet::CBullet(glm::vec3 _dirVec, float _damage) :
	m_damage(_damage),
	m_counter(500),
	m_bulletSpeed(0.5f)
{
	this->m_friction = 1.0f;
	this->m_velocity = glm::normalize(_dirVec) * m_bulletSpeed;

	this->m_IsModel = false;
	this->InitializeObject(
		cMeshMgr->GetMesh(SPHERE), 
		cAssetMgr->GetTextureID("TITANFALL"), 
		cAssetMgr->GetProgramID("ModelBlinnPhong")
	);
}


CBullet::~CBullet()
{

}

void CBullet::UpdateGameObeject()
{
	if (this->m_counter < 0)
	{
		CSceneMgr::GetInstance()->GetCurrentScene()->DestroyInstance(this);
		std::cout << "Bullet Destroyed. \n";
	}
	else this->m_counter--;

	this->PhysicsUpdate();
}
