/*
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
*/

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
#include "SinglePlayerScene.h"

// Class Pointer
static CInput* cInputMgr = CInput::GetInstance();

CPlayer::CPlayer(CModel* _model, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f),
	m_AbleToShoot(true)
{
	m_tag = "Player";
	m_friction = 0.9f;
	m_ColliderRad = 1.5f;

	m_IsModel = true;
	InitializeObject(_model, _programID);
	SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
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
		m_health -= 5;
	}
}

void CPlayer::ProcessMovement()
{
	glm::vec3 resultVec;

	if ((cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_HOLD || cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS))
	{
		resultVec.z -= 1;
	}
	if ((cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_HOLD || cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS))
	{
		resultVec.z += 1;
	}
	if ((cInputMgr->g_cKeyState[(unsigned char)'a'] == INPUT_HOLD || cInputMgr->g_cKeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS))
	{
		resultVec.x -= 1;
	}
	if ((cInputMgr->g_cKeyState[(unsigned char)'d'] == INPUT_HOLD || cInputMgr->g_cKeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS))
	{
		resultVec.x += 1;
	}

	if (resultVec != glm::vec3())
	{
		// Add the speed force to the direction
		this->m_velocity = glm::normalize(resultVec) * m_movementSpd;
	}
}

void CPlayer::ProcessShooting()
{
	if (cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS && m_AbleToShoot)
	{
		cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
		//m_pSound.SetSoundAdress("Resources/Sound/TankFiring.wav");
		CBullet* bullet = new CBullet(m_velocity, 10);
		CSceneMgr::GetInstance()->GetCurrentScene()->Instantiate(bullet, glm::vec3(m_Position.x, 1.0f, m_Position.z));
		//m_AbleToShoot = false;
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
	case SCORE:
	{
		CSinglePlayerScene* temp = dynamic_cast<CSinglePlayerScene*>(CSceneMgr::GetInstance()->GetCurrentScene());
		temp->AddScore(300);
		break;
	}
	case MOVESPD:
	{
		m_movementSpd += 0.05f;
		if (m_movementSpd >= 0.5f) // Cap the movement speed
		{
			m_movementSpd = 0.5f;
		}
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
		DestroyObject();
	}
}

int CPlayer::GetHealth() const
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
