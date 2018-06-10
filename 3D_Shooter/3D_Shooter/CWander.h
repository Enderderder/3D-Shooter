//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CWander.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//
#ifndef CWANDER_H
#define CWANDER_H

#include "Utility.h"
#include "Player.h"
class CWander
{
public:
	CWander();
	~CWander();

	float rand_FloatRange(float a, float b)
	{
		return ((b - a) * ((float)rand() / RAND_MAX)) + a;
	}

	glm::vec3 UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos);
};

#endif