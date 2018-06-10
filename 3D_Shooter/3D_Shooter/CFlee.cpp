#include "CFlee.h"



CFlee::CFlee()
{
}


CFlee::~CFlee()
{
}

glm::vec3 CFlee::UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentPos)
{
	glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);
	const double PanicDistance = 1.0f ;
	
	if (IsNotPanicArea(_Target->GetPosition(), _AgentPos))
	{
		resultMovement = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	else
	{
		resultMovement = glm::normalize(_AgentPos - _Target->GetPosition());
	}

	return resultMovement;
}

bool CFlee::IsNotPanicArea(glm::vec3 _PlayerPos, glm::vec3 _AIPos)
{
	if (_PlayerPos.x > _AIPos.x - 7.0f && _PlayerPos.x < _AIPos.x + 7.0f && _PlayerPos.z > _AIPos.x - 7.0f && _PlayerPos.z < _AIPos.z + 7.0f)
	{
		return false;
	}

	return true;
}
