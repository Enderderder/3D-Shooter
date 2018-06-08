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

CBullet::CBullet(glm::vec3 _dirVec, float _damage) :
	m_damage(_damage),
	m_counter(10)
{
	this->m_friction = 1.0f;
	this->m_velocity = glm::normalize(_dirVec) * m_bulletSpeed;

	this->m_IsModel = false;
	this->InitializeObject(CMeshMgr::GetInstance().GetMesh(SPHERE), _textureID, _programID);
}


CBullet::~CBullet()
{

}

void CBullet::UpdateGameObeject()
{
	if (m_counter > 0)
	{
		CSceneMgr::GetInstance()->GetCurrentScene()->DestroyInstance(this);
		std::cout << "Bullet Destroyed. \n";
	}
	else m_counter--;
}
