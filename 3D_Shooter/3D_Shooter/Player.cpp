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

// Class Pointer
static CInput* cInput = CInput::GetInstance();

CPlayer::CPlayer(CMesh* _mesh, GLuint _textureID, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f)
{
	m_friction = 0.9f;

	this->m_IsModel = false;
	this->InitializeObject(_mesh, _textureID, _programID);
}

CPlayer::CPlayer(CModel* _model, GLuint _programID) :
	m_health(100),
	m_attackSpd(1.0f),
	m_movementSpd(0.25f)
{
	m_friction = 0.9f;

	this->m_IsModel = true;
	this->InitializeObject(_model, _programID);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
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

	float fMag = sqrtf(powf(resultVec.x, 2) + powf(resultVec.y, 2) + powf(resultVec.z, 2));
	if (fMag > 0.0f)
	{
		this->m_velocity = (resultVec / fMag) * m_movementSpd;
	}

	PhysicsUpdate();
}