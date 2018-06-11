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

#ifndef ARRIVAL_H
#define ARRIVAL_H

#include "Utility.h"
#include "Player.h"


class CArrival
{
public:
	CArrival();
	~CArrival();

	glm::vec3 UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos);
};

#endif //!ARRIVAL_H