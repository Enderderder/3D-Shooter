/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : PhysicObject.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

// This Include
#include "PhysicObject.h"

// Library Include
#include <cmath>

CPhysicObject::CPhysicObject()
{
	m_HasCollider = true;
}

CPhysicObject::CPhysicObject(CMesh* _mesh, GLuint _textureID, GLuint _programID)
{
	InitializeObject(_mesh, _textureID, _programID);
}

CPhysicObject::CPhysicObject(CModel* _model, GLuint _programID)
{
	InitializeObject(_model, _programID);
}

CPhysicObject::~CPhysicObject()
{}

void CPhysicObject::PhysicsUpdate()
{
	// Change the Direction player facing
	if (m_velocity.x < 0 && m_velocity.z > 0) // Right Down
	{
		SetRotationY(135.0f);
	}
	else if (m_velocity.x < 0 && m_velocity.z < 0) // Right Up
	{
		SetRotationY(45);
	}
	else if (m_velocity.x > 0 && m_velocity.z > 0) // Left Down
	{
		SetRotationY(-135.0f);
	}
	else if (m_velocity.x > 0 && m_velocity.z < 0) // Left Up
	{
		SetRotationY(-45.0f);
	}
	else if (m_velocity.x < 0) // Right
	{
		SetRotationY(90.0f);
	}
	else if (m_velocity.x > 0) // Left
	{
		SetRotationY(-90.0f);
	}
	else if (m_velocity.z > 0) // Down
	{
		SetRotationY(180.0f);
	}
	else if (m_velocity.z < 0) // Up
	{
		SetRotationY(0.0f);
	}



	// Use the velocity to move the object
	AddPosition(m_velocity);

	// Friction affecting the velocity
	m_velocity = m_velocity * m_friction;
}

glm::vec3 CPhysicObject::GetVelocity() const
{
	return m_velocity;
}
