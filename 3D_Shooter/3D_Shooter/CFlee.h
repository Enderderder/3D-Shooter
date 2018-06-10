//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CFlee.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//
#ifndef CFLEE_H
#define CFLEE_H

#include "Utility.h"
#include "Player.h"

class CFlee
{
public:
	CFlee();
	~CFlee();

	glm::vec3 UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos);
	bool IsNotPanicArea(glm::vec3 _PlayerPos, glm::vec3 _AIPos);
};
#endif
