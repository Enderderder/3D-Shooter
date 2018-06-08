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
	m_movementSpd(0.25f),
	m_attackSpd(1)
{
	this->m_IsModel = false;
	this->InitializeObject(_mesh, _textureID, _programID);
}

CPlayer::CPlayer(CModel* _model, GLuint _programID) :
	m_health(100),
	m_movementSpd(0.25f),
	m_attackSpd(1)
{
	this->m_IsModel = true;
	this->InitializeObject(_model, _programID);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
{
	glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);

	if ((cInput->g_cKeyState[(unsigned char)'w'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS) && this->m_Position.z >= -18.8f)
	{
		resultMovement.z -= m_movementSpd;
	}
	if ((cInput->g_cKeyState[(unsigned char)'s'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS) && this->m_Position.z <= 18.8f)
	{
		resultMovement.z += m_movementSpd;
	}
	if ((cInput->g_cKeyState[(unsigned char)'a'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS) && this->m_Position.x >= -18.8f)
	{
		resultMovement.x -= m_movementSpd;
	}
	if ((cInput->g_cKeyState[(unsigned char)'d'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS) && this->m_Position.x <= 18.8f)
	{
		resultMovement.x += m_movementSpd;
	}

	float fMag = sqrtf(powf(resultMovement.x, 2) + powf(resultMovement.z, 2));
	if (fMag != 0.0f)
	{
		glm::vec3 uniVec = resultMovement / fMag;
		resultMovement = uniVec * m_movementSpd;
		this->AddPosition(resultMovement);
	}
}

