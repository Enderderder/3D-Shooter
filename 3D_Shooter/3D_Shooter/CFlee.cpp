#include "CFlee.h"



CFlee::CFlee()
{
}


CFlee::~CFlee()
{
}

glm::vec3 CFlee::UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos, glm::vec3 _AgentVel)
{
	glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);
	const double PanicDistance = 1.0f ;
	
	if (IsNotPanicArea(_Target->GetPosition(), _AgentPos))
	{
		resultMovement = glm::vec3();
	}

	else
	{
		glm::vec3 desiredVelo = glm::normalize(_AgentPos - _Target->GetPosition());
		desiredVelo *= _movementSpd;

		glm::vec3 curVelo = _AgentVel;

		glm::vec3 Steering = (_AgentPos + desiredVelo) - (_AgentPos + curVelo);
		Steering /= 50.0f;
		resultMovement = Steering;
	}

	return resultMovement;
}

bool CFlee::IsNotPanicArea(glm::vec3 _PlayerPos, glm::vec3 _AIPos)
{
	if (_PlayerPos.x > _AIPos.x - 10.0f && _PlayerPos.x < _AIPos.x + 10.0f &&
		_PlayerPos.z > _AIPos.x - 10.0f && _PlayerPos.z < _AIPos.z + 10.0f)
	{
		return false;
	}

	return true;
}
