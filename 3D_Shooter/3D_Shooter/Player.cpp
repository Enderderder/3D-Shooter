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
#include "PowerUps.h"
#include "CAIMgr.h"

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
	// Process the Input of movement and shooting
	ProcessMovement();
	ProcessShooting();

	// Physical Object must have
	PhysicsUpdate();

	// Check if there is any boundary issue
	ProcessBoundary();

	// Check to see if the player dies
	CheckDeath();
}

void CPlayer::OnCollision(CGameObject* _other)
{
	if (_other->GetTag() == "PowerUp")
	{
		// Cast it to the other Object
		CPowerUps* other = dynamic_cast<CPowerUps*>(_other);
		ProcessPowerUpEffect(other->GetEffect());
	}
	else if (_other->GetTag() == "Enemy")
	{
		m_health -= 10;
	}
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
		//m_pSound.SetSoundAdress("Resources/Sound/TankFiring.wav");
		CBullet* bullet = new CBullet(m_velocity, 10);
		CSceneMgr::GetInstance()->GetCurrentScene()->Instantiate(bullet, glm::vec3(m_Position.x, 1.0f, m_Position.z));
		m_AbleToShoot = false;
	}
	else if (cInput->g_cKeyState[(unsigned char)'k'] == INPUT_RELEASED && !m_AbleToShoot)
	{
		m_AbleToShoot = true;
	}
}

void CPlayer::ProcessBoundary()
{
	// If the position goes out of the boundary
	if (CheckBoarderUp(m_Position.z) == false)
	{
		SetPositionZ(BorderUp);
	}
	else if (CheckBoarderDown(m_Position.z) == false)
	{
		SetPositionZ(BorderDown);
	}
	if (CheckBoarderLeft(m_Position.x) == false)
	{
		SetPositionX(BorderLeft);
	}
	else if (CheckBoarderRight(m_Position.x) == false)
	{
		SetPositionX(BorderRight);
	}
}

void CPlayer::ProcessPowerUpEffect(EPOWERUPEFFECT _effect)
{
	switch (_effect)
	{
	case HEAL:
	{
		m_health += 30;
		if (m_health > 100)
		{
			m_health = 100;
		}
		break;
	}
	case PWOER:
	{
		
		break;
	}
	case MOVESPD:
	{
		m_movementSpd += 0.1f;
		break;
	}
	case ATKSPD:
	{
		m_attackSpd += 1;
		break;
	}

	default:
		break;
	}
}

void CPlayer::CheckDeath()
{
	if (m_health <= 0)
	{
		
	}
}

int CPlayer::GetLife() const
{
	return(m_health);
}

bool CPlayer::CheckBoarderUp(float _posZ)
{
	if (_posZ >= BorderUp)
	{
		return true;
	} else return false;
}

bool CPlayer::CheckBoarderDown(float _posZ)
{
	if (_posZ <= BorderDown)
	{
		return true;
	}
	else return false;
}

bool CPlayer::CheckBoarderLeft(float _posX)
{
	if (_posX >= BorderLeft)
	{
		return true;
	}
	else return false;
}

bool CPlayer::CheckBoarderRight(float _posX)
{
	if (_posX <= BorderRight)
	{
		return true;
	}
	else return false;
}
