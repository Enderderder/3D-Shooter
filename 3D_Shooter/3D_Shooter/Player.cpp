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

CPlayer::CPlayer(CMesh* _mesh, GLuint* _texture, GLuint* _program)
{
	this->InitializeObject(_mesh, _texture, _program);
}

CPlayer::~CPlayer()
{}

void CPlayer::UpdateGameObeject()
{

}
