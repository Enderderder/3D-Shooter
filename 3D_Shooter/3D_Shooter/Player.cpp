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
	m_movementSpd(0.25f)
{
	this->m_tag = "Player";
	this->m_friction = 0.9f;

	this->m_IsModel = false;
	this->InitializeObject(_mesh, _textureID, _programID);
}

CPlayer::CPlayer(CModel* _model, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f)
{
	this->m_tag = "Player";
	this->m_friction = 0.9f;
	//this->m_ColliderRad

	this->m_IsModel = true;
	this->InitializeObject(_model, _programID);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
{
	this->ProcessMovement();
	this->ProcessShooting();

	// Physical Object must have
	PhysicsUpdate();
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
	if (cInput->g_cKeyState[(unsigned char)'k'] == INPUT_FIRST_PRESS)
	{
		CBullet* bullet = new CBullet(m_velocity, 10);
		CSceneMgr::GetInstance()->GetCurrentScene()->Instantiate(bullet, this->m_Position);
	}
}
