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
	glm::vec3 resultAiSteering;

	switch (AI)
	{
	case SEEK:
	{
		resultAiSteering += AiSeek(m_pTarget->GetPosition());
		
		break;
	}

	case FLEE:
	{
		resultAiSteering += AiFlee(m_pTarget->GetPosition());
		
		break;
	}

	case PURSUE:
	{
		resultAiSteering += AiPursue(m_pTarget);

		break;
	}

	case WANDER:
	{
		resultAiSteering += AiWander();
		break;
	}

	case ARRIVE:
	{
		resultAiSteering += AiArrival(m_pTarget);
		resultAiSteering += Separate(CSceneMgr::GetInstance()->GetCurrentScene()->GetObjectVec());
		break;
	}

	case FLOCK:
	{
		resultAiSteering += Separate(CSceneMgr::GetInstance()->GetCurrentScene()->GetObjectVec());
		break;
	}

	case LEADERFOLLOW:
	{

		break;
	}

	default:
		break;
	}

	// Apply the steering force to the object
	m_velocity += resultAiSteering;

	// Make sure the speed of the agent does not go beyong the limit
	if (glm::length(m_velocity) > m_movementSpd && glm::length(m_velocity) != 0.0f)
	{
		m_velocity = glm::normalize(m_velocity) * m_movementSpd;
	}

	// Test no matter what in the game if the AI touches a wall
	m_velocity += AiWallBounce();


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

glm::vec3 CAIMgr::AiSeek(glm::vec3 _TargetPoint)
{
	glm::vec3 desiredVel = glm::normalize(_TargetPoint - m_Position);
	desiredVel *= m_movementSpd;

	glm::vec3 steering = (desiredVel) - (m_velocity);
	steering /= 25.0f;

	// Apply the steering force to the agent
	return steering;
}

glm::vec3 CAIMgr::AiFlee(glm::vec3 _TargetPoint)
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
		return steering;
	}
}

void  CAIMgr::AiLeaderFollow(glm::vec3 _TargetPoint)
{

}

glm::vec3 CAIMgr::AiPursue(CGameObject* _Target)
{
	// cast the target object to a specified Physics Object which contains the 
	CPhysicObject* target = dynamic_cast<CPhysicObject*>(_Target);

	// Get the prediction point of the target | certain frames ahead
	glm::vec3 futurePoint = target->GetPosition() + target->GetVelocity() * 10.0f;

	return AiSeek(futurePoint);
}

glm::vec3 CAIMgr::AiArrival(CGameObject* _Target)
{
	glm::vec3 desiredVel = glm::normalize(_Target->GetPosition() - m_Position);
	desiredVel *= m_movementSpd;

	float PlayerRadius = 15.0f;
	if (glm::distance(_Target->GetPosition(), m_Position) < PlayerRadius)
	{
		desiredVel *= glm::distance(_Target->GetPosition(), m_Position) / PlayerRadius;
	}

	glm::vec3 Steering = (m_Position + desiredVel) - (m_Position + m_velocity);
	Steering /= 25.0f;
	
	return Steering;
}

glm::vec3 CAIMgr::AiWander()
{
	// Calc where the circle is
	glm::vec3 circleCentre = glm::normalize(m_velocity)* 1.0f; // CIRCLE_DIS

	// Calc displacement length on the circle
	glm::vec3 displacement(0.0f, 0.0f, -1.0f);
	displacement = displacement * 5.0f; // CIRCLE_RAD

	// Set the angle on to the circle
	SetAngle(displacement, m_WanderAngle);

	// Randomly add some angle to the agent
	m_WanderAngle += -5 + float(rand() % 10);
	//std::cout << m_WanderAngle << std::endl;

	// Calc the final wander force thats been add to the agent
	glm::vec3 wanderForce = circleCentre + displacement;

	return wanderForce;
}

glm::vec3 CAIMgr::AiWallBounce()
{
	glm::vec3 steering;

	if (m_Position.x < -18.5f)
	{
		glm::vec3 desiredVel = glm::vec3(m_movementSpd, 0.0f, m_velocity.z);
		steering = desiredVel - m_velocity;
	}
	else if (m_Position.x > 18.5f)
	{
		glm::vec3 desiredVel = glm::vec3(-m_movementSpd, 0.0f, m_velocity.z);
		steering = desiredVel - m_velocity;
	}
	if (m_Position.z < -18.5f)
	{
		glm::vec3 desiredVel = glm::vec3(m_velocity.x, 0.0f, m_movementSpd);
		steering = desiredVel - m_velocity;
	}
	else if (m_Position.z > 18.5f)
	{
		glm::vec3 desiredVel = glm::vec3(m_velocity.x, 0.0f, -m_movementSpd);
		steering = desiredVel - m_velocity;
	}
	
	//If there is a wall collide, then bounce it off
	if (steering != glm::vec3())
	{
		steering /= 25.0f;
		return steering;
	}
	else return glm::vec3();
}

glm::vec3 CAIMgr::Separate(std::vector<CGameObject*> _objVec)
{
	float desiredSeparateDis = 2.0f;
	glm::vec3 sumVec;
	int counter = 0;

	for (auto _other : _objVec)
	{
		if (_other->GetTag() == "Enemy")
		{
			float distance = glm::distance(m_Position, _other->GetPosition());

			if ((distance > 0.0f) && (distance < desiredSeparateDis))
			{
				glm::vec3 dir = glm::normalize(m_Position - _other->GetPosition());
				sumVec += dir;
				counter++;
			}
		}
	}

	if (counter > 0)
	{
		sumVec /= counter;
		sumVec = glm::normalize(sumVec) * m_movementSpd;

		glm::vec3 steering = sumVec + m_velocity;
		steering /= 0.25f;

		return steering;
	}

	return glm::vec3();
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