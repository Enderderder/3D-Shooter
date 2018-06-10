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
	
	if ( _AgentPos.x <= PanicDistance && _AgentPos.z <= PanicDistance)
	{
		resultMovement = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	else
	{
		resultMovement = glm::normalize(_AgentPos - _Target->GetPosistion(_Target));
	}

	return(resultMovement);
}
