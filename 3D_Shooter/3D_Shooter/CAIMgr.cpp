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

// Local Include
#include "CAIMgr.h"
#include "SceneMgr.h"

CAIMgr::CAIMgr(CMesh* _mesh, GLuint _textureID, GLuint _programID, AIType _AIType, CGameObject* _Target) :
	
	m_movementSpd(0.5f)
{
	m_velocity = glm::vec3(1.0f, 0.0f, -1.0f) * m_movementSpd;
	m_tag = "Enemy";
	m_ColliderRad = 1.0f;
	m_friction = 1.0f;
	AI = _AIType;
	m_pTarget = _Target;
	InitializeObject(_mesh, _textureID, _programID);
}

void CAIMgr::UpdateGameObeject()
{
	switch (AI)
	{
	case SEEK:
	{
		AiSeek(m_pTarget->GetPosition());
		if (glm::distance(m_Position, m_pTarget->GetPosition()) < 15.0f)
		{
			AI = FLEE;
		}
		break;
	}

	case FLEE:
	{
		AiFlee(m_pTarget->GetPosition());
		if (glm::distance(m_Position, m_pTarget->GetPosition()) > 15.0f)
		{
			//AI = SEEK;
		}
		break;
	}

	case PURSUE:
	{
		AiPursue(m_pTarget);

		break;
	}

	case WANDER:
	{
		AiWander();
		if (glm::length(m_velocity) > m_movementSpd && glm::length(m_velocity) != 0.0f)
		{
			m_velocity = glm::normalize(m_velocity) * m_movementSpd;
		}
		break;
	}

	case CONTAINMENT:
	{

		break;
	}

	default:
		break;
	}

	// Test no matter what in the game if the AI touches a wall
	AiWallBounce();

	// Make sure the speed of the agent does not go beyong the limit
	if (glm::length(m_velocity) > m_movementSpd && glm::length(m_velocity) != 0.0f)
	{
		m_velocity = glm::normalize(m_velocity) * m_movementSpd;
	}

	this->PhysicsUpdate();
}

void CAIMgr::OnCollision(CGameObject* _other)
{
	if (_other->GetTag() == "Bullet")
	{
		//DestroyObject();
		CSceneMgr::GetInstance()->GetCurrentScene()->AddScore(100);
	}
	if (_other->GetTag() == "Player")
	{
		//DestroyObject();
	}
}

void CAIMgr::AiSeek(glm::vec3 _TargetPoint)
{
	glm::vec3 desiredVel = glm::normalize(_TargetPoint - m_Position);
	desiredVel *= m_movementSpd;

	glm::vec3 steering = (m_Position + desiredVel) - (m_Position + m_velocity);
	steering /= 25.0f;

	// Apply the steering force to the agent
	m_velocity += steering;
}

void CAIMgr::AiFlee(glm::vec3 _TargetPoint)
{
	if (IsNotPanicArea(_TargetPoint))
	{
		// Target is not close enough, stop moving
		m_velocity = glm::vec3();
	}
	else
	{
		glm::vec3 desiredVel = glm::normalize(m_Position - _TargetPoint);
		desiredVel *= m_movementSpd;

		glm::vec3 steering = (m_Position + desiredVel) - (m_Position + m_velocity);
		steering /= 25.0f;

		// Apply the steering force to the agent
		m_velocity += steering;
	}
}

void CAIMgr::AiPursue(CGameObject* _Target)
{
	// cast the target object to a specified Physics Object which contains the 
	CPhysicObject* target = dynamic_cast<CPhysicObject*>(_Target);

	// Get the prediction point of the target | certain frames ahead
	glm::vec3 futurePoint = target->GetPosition() + target->GetVelocity() * 10.0f;

	AiSeek(futurePoint);
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

void CAIMgr::AiWallBounce()
{
	glm::vec3 steering;

	if (m_Position.x < -19.0f)
	{
		glm::vec3 desiredVel = glm::vec3(m_movementSpd, 0.0f, m_velocity.z);
		steering = desiredVel - m_velocity;
		steering /= 25.0f;
		m_velocity += steering;
	}
	else if (m_Position.x > 19.0f)
	{
		glm::vec3 desiredVel = glm::vec3(-m_movementSpd, 0.0f, m_velocity.z);
		steering = desiredVel - m_velocity;
		steering /= 25.0f;
		m_velocity += steering;
	}
	if (m_Position.z < -19.0f)
	{
		glm::vec3 desiredVel = glm::vec3(m_velocity.x, 0.0f, m_movementSpd);
		steering = desiredVel - m_velocity;
		steering /= 25.0f;
		m_velocity += steering;
	}
	else if (m_Position.z > 19.0f)
	{
		glm::vec3 desiredVel = glm::vec3(m_velocity.x, 0.0f, -m_movementSpd);
		steering = desiredVel - m_velocity;
		steering /= 25.0f;
		m_velocity += steering;
	}
	
	// If there is a wall collide, then bounce it off
	//if (steering != glm::vec3())
	//{
	//	steering /= 25.0f;
	//	m_velocity += steering;
	//}
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