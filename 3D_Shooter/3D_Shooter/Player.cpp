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

// Local Include
#include "Input.h"

// Class Pointer
static CInput* cInput = CInput::GetInstance();

CPlayer::CPlayer(CMesh* _mesh, GLuint* _texture, GLuint* _program)
	:	m_health(100),
		m_movementSpd(0.25f),
		m_attackSpd(1)
{
	this->InitializeObject(_mesh, _texture, _program);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
{
	if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS)
	{
		this->AddPosition(glm::vec3(0.0f, 0.0f, -m_movementSpd));
	}
	if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS)
	{
		this->AddPosition(glm::vec3(0.0f, 0.0f, m_movementSpd));
	}
	if (cInput->g_cKeyState[(unsigned char)'a'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS)
	{
		this->AddPosition(glm::vec3(-m_movementSpd, 0.0f, 0.0f));
	}
	if (cInput->g_cKeyState[(unsigned char)'d'] == INPUT_HOLD || cInput->g_cKeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS)
	{
		this->AddPosition(glm::vec3(m_movementSpd, 0.0f, 0.0f));
	}
}
