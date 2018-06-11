#include "Arrival.h"



CArrival::CArrival()
{
}


CArrival::~CArrival()
{
}

glm::vec3 CArrival::UpdateGameObject(CGameObject * _Target, float _movementSpd, glm::vec3 _AgentPos)
{
	glm::vec3 resultMovement;

	resultMovement = glm::normalize(_Target->GetPosition() - _AgentPos);

	return(resultMovement);
}
