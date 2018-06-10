#include "CSeek.h"




CSeek::CSeek()
{
}


CSeek::~CSeek()
{
}

glm::vec3 CSeek::UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos)
{
	glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);

	resultMovement = glm::normalize(_Target->GetPosistion(_Target) - _AgentPos);

	return(resultMovement);
}
