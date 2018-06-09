//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Player.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "Player.h"

// Library Include
#include <cmath>

// Local Include
#include "Input.h"
#include "SceneMgr.h"
#include "CBullet.h"

// Class Pointer
static CInput* cInput = CInput::GetInstance();

CPlayer::CPlayer(CMesh* _mesh, GLuint _textureID, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f),
	m_AbleToShoot(true)
{
	m_tag = "Player";
	m_friction = 0.9f;
	m_ColliderRad = 2.0f;

	m_IsModel = false;
	InitializeObject(_mesh, _textureID, _programID);
}

CPlayer::CPlayer(CModel* _model, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f),
	m_AbleToShoot(true)
{
	m_tag = "Player";
	m_friction = 0.9f;
	m_ColliderRad = 2.0f;

	m_IsModel = true;
	InitializeObject(_model, _programID);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
{
	ProcessMovement();
	ProcessShooting();

	// Physical Object must have
	PhysicsUpdate();
}

void CPlayer::OnCollision(CGameObject* _other)
{
	/* Test with our own bullet************************************
	if (_other->GetTag() == "Bullet")
	{
		// Cast it to the other Object
		CBullet* other = dynamic_cast<CBullet*>(_other);
		float damageTaken = other->GetDamage();
		std::cout << "Damage Taken: " << damageTaken << "\n";

		// Player Take the damage
		m_health -= damageTaken;
	}
	/**************************************************************/
}

void CPlayer::ProcessMovement()
{
	glm::vec3 resultVec;

	if ((cInput->g_cKeyState[(unsigned char)'w'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS))
	{
		resultVec.z -= 1;
	}
	if ((cInput->g_cKeyState[(unsigned char)'s'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS))
	{
		resultVec.z += 1;
	}
	if ((cInput->g_cKeyState[(unsigned char)'a'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS))
	{
		resultVec.x -= 1;
	}
	if ((cInput->g_cKeyState[(unsigned char)'d'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS))
	{
		resultVec.x += 1;
	}

	// If player actually have movement input
	if (resultVec != glm::vec3())
	{
		// Add the speed force to the direction
		this->m_velocity = glm::normalize(resultVec) * m_movementSpd;
	}
}

void CPlayer::ProcessShooting()
{
	if (cInput->g_cKeyState[(unsigned char)'k'] == INPUT_FIRST_PRESS && m_AbleToShoot)
	{
		CBullet* bullet = new CBullet(m_velocity, 10);
		CSceneMgr::GetInstance()->GetCurrentScene()->Instantiate(bullet, m_Position);
		m_AbleToShoot = false;
	}
	else if (cInput->g_cKeyState[(unsigned char)'k'] == INPUT_RELEASED && !m_AbleToShoot)
	{
		m_AbleToShoot = true;
	}
}
