#include "CWander.h"



CWander::CWander()
{
}


CWander::~CWander()
{
}

glm::vec3 CWander::UpdateGameObject(CGameObject* _Target, float _movementSpd, glm::vec3 _AgentVel)
{
	glm::vec3 wanderForce;

	// Calc where the circle is
	glm::vec3 circleCentre = _AgentVel;
	circleCentre = glm::normalize(circleCentre);
	circleCentre = circleCentre * 3.0f; // CIRCLE_DIS
	
	// Calc displacement length on the circle
	glm::vec3 displacement(1.0f, 0.0f, 0.0f);
	displacement = displacement * 2.0f; // CIRCLE_RAD

	// Set the angle on to the circle
	SetAngle(displacement, m_WanderAngle);

	// Randomly add some angle to the agent
	m_WanderAngle += float(rand() % 2 - 1);
	std::cout << m_WanderAngle << std::endl;
	// Calc the final wander force thats been add to the agent
	wanderForce = circleCentre + displacement;

	return(wanderForce);
}

void CWander::SetAngle(glm::vec3& _vector, float _angle)
{
	float length = glm::length(_vector);

	_vector.x = cosf(glm::radians(_angle)) * length;
	_vector.z = sinf(glm::radians(_angle)) * length;
}
