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

CBullet::CBullet(glm::vec3 _dirVec, int _damage) :
	m_damage(_damage),
	m_counter(500),
	m_bulletSpeed(0.5f)
{
	m_tag = "Bullet";
	m_ColliderRad = 0.5f;
	m_friction = 1.0f;
	m_velocity = glm::normalize(_dirVec) * m_bulletSpeed;

	m_IsModel = false;
	InitializeObject(
		cMeshMgr->GetMesh(SPHERE), 
		cAssetMgr->GetTextureID("Bullet"), 
		cAssetMgr->GetProgramID("RimLight")
	);

	SetScale(glm::vec3(0.5));
}


CBullet::~CBullet()
{

}

void CBullet::UpdateGameObeject()
{
	if (m_counter < 0)
	{
		DestroyObject();
	}
	else m_counter--;

	PhysicsUpdate();
}

void CBullet::OnCollision(CGameObject* _other)
{
	if (_other->GetTag() != "Player")
	{
		DestroyObject();
	}
}

int CBullet::GetDamage() const
{
	return m_damage;
}
