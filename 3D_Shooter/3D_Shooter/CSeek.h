//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CSeek.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef CSEEK_H
#define CSEEK_H

#include "Utility.h"
#include "Player.h"


class CSeek
{
public:
	CSeek();
	~CSeek();

	glm::vec3 UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos, glm::vec3 _AgentVel);
};

#endif //!CSEEK_H
