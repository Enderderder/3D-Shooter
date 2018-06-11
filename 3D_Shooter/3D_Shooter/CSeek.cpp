#include "CSeek.h"




CSeek::CSeek()
{
}


CSeek::~CSeek()
{
}

glm::vec3 CSeek::UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos, glm::vec3 _AgentVel)
{
	glm::vec3 desiredVelo = glm::normalize(_Target->GetPosition() - _AgentPos);
	desiredVelo *= _movementSpd;

	glm::vec3 curVelo = _AgentVel;

	glm::vec3 Steering = (_AgentPos + desiredVelo) - (_AgentPos + curVelo);
	Steering /= 50.0f;

	return(Steering);
}
