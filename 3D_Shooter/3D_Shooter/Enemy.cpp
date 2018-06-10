/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Enemy.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Include
#include "Enemy.h"

// Local Include
#include "CBullet.h"

CEnemy::CEnemy(CMesh * _mesh, GLuint _textureID, GLuint _programID) :
	m_health(20),
	m_damage(10),
	m_movementSpd(0.1f)
{
	m_tag = "Enemy";
	m_friction = 0.9f;
	m_ColliderRad = 1.0f;

	m_IsModel = false;
	InitializeObject(_mesh, _textureID, _programID);
}

CEnemy::~CEnemy()
{}

void CEnemy::UpdateGameObeject()
{
	ProcessAI();


	// Physical Object must have
	PhysicsUpdate();
}

void CEnemy::OnCollision(CGameObject* _other)
{
	if (_other->GetTag() == "Bullet")
	{
		// Cast it to the other Object
		CBullet* other = dynamic_cast<CBullet*>(_other);
		int damageTaken = other->GetDamage();

		// Enemy takes the damage from the bullet
		m_health -= damageTaken;
	}
	else if (_other->GetTag() == "Player")
	{
		DestroyObject();
		
	}
}

void CEnemy::ProcessAI()
{

}
