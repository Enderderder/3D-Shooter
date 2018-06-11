//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CAIMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef AIMgr_H
#define AIMgr_H

#include "CAIMgr.h"
#include "SceneMgr.h"

CAIMgr::CAIMgr(CMesh* _mesh, GLuint _textureID, GLuint _programID, AIType _AIType, CGameObject* _Target) :
	
	m_movementSpd(0.2f)
{
	m_velocity = glm::vec3(1.0f, 0.0f, -1.0f) * m_movementSpd;
	m_tag = "Enemy";
	m_ColliderRad = 1.0f;
	m_friction = 1.0f;
	AI = _AIType;
	m_pTarget = _Target;
	InitializeObject(_mesh, _textureID, _programID);
}

//CAIMgr::CAIMgr(CModel* _model, GLuint _programID, AIType _AIType, CGameObject* _Target) :
//
//
//	m_movementSpd(1.0f)
//
//{
//	m_tag = "Enemey";
//	AI = _AIType;
//	m_pTarget = _Target;
//	InitializeObject(_model, _programID);
//}

void CAIMgr::UpdateGameObeject()
{
	//glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);

	switch (AI)
	{
	case SEEK:
	{
		AiSeek(m_pTarget);
		if (glm::distance(m_Position, m_pTarget->GetPosition()) < 15.0f)
		{
			AI = FLEE;
		}
	}
		break;

	case FLEE:
	{
		AiFlee(m_pTarget);
		if (glm::distance(m_Position, m_pTarget->GetPosition()) > 15.0f)
		{
			AI = SEEK;
		}
	}
		break;

	case WANDER:
	{
		//resultMovement = m_pWander.UpdateGameObject(m_pTarget, m_movementSpd, m_velocity);
		AiWander();
	}
		break;

	case CONTAINMENT:
	{

	}
		break;

	default:
	{
	
	}
		break;
	}

	if (glm::length(m_velocity) > m_movementSpd && glm::length(m_velocity) != 0.0f)
	{
		m_velocity = glm::normalize(m_velocity) * m_movementSpd;
	}

	this->PhysicsUpdate();
}

void CAIMgr::OnCollision(CGameObject * _other)
{
	if (_other->GetTag() == "Bullet")
	{
		DestroyObject();
		CSceneMgr::GetInstance()->GetCurrentScene()->AddScore(100);
	}
	if (_other->GetTag() == "Player")
	{
		//DestroyObject();
	}
}

void CAIMgr::AiSeek(CGameObject* _Target)
{
	glm::vec3 desiredVelo = glm::normalize(_Target->GetPosition() - m_Position);
	desiredVelo *= m_movementSpd;

	glm::vec3 Steering = (m_Position + desiredVelo) - (m_Position + m_velocity);
	Steering /= 25.0f;

	m_velocity += Steering;
	if (glm::length(m_velocity) > m_movementSpd && glm::length(m_velocity) != 0.0f)
	{
		m_velocity = glm::normalize(m_velocity) * m_movementSpd;
	}
}

void CAIMgr::AiFlee(CGameObject* _Target)
{
	if (IsNotPanicArea(_Target->GetPosition()))
	{
		// Target is not close enough, stop moving
		m_velocity = glm::vec3();
	}

	else
	{
		glm::vec3 desiredVelo = glm::normalize(m_Position - _Target->GetPosition());
		desiredVelo *= m_movementSpd;

		glm::vec3 curVelo = m_velocity;

		glm::vec3 Steering = (m_Position + desiredVelo) - (m_Position + curVelo);
		Steering /= 25.0f;

		// Apply the steering force to the AI
		m_velocity += Steering;
	}
}

void CAIMgr::AiArrival(CGameObject* _Target)
{

}

void CAIMgr::AiWander()
{
	glm::vec3 wanderForce;

	// Calc where the circle is
	glm::vec3 circleCentre = m_velocity;
	circleCentre = glm::normalize(circleCentre);
	circleCentre = circleCentre * 3.0f; // CIRCLE_DIS

	// Calc displacement length on the circle
	glm::vec3 displacement(1.0f, 0.0f, 0.0f);
	displacement = displacement * 5.0f; // CIRCLE_RAD

	// Set the angle on to the circle
	SetAngle(displacement, m_WanderAngle);

	// Randomly add some angle to the agent
	m_WanderAngle += -3 + float(rand() % 6);
	std::cout << m_WanderAngle << std::endl;
	// Calc the final wander force thats been add to the agent
	wanderForce = circleCentre + displacement;

	m_velocity += wanderForce;
}

bool CAIMgr::IsNotPanicArea(glm::vec3 _PlayerPos)
{
	if (glm::distance(_PlayerPos, m_Position) > 10.0f)
	{
		return true;
	}
	return false;
}

// Use the angle value to turn the vector
void CAIMgr::SetAngle(glm::vec3& _vector, float _angle)
{
	float length = glm::length(_vector);

	_vector.x = cosf(glm::radians(_angle)) * length;
	_vector.z = sinf(glm::radians(_angle)) * length;
}

CAIMgr::~CAIMgr()
{}


#endif // !AIMgr_H
