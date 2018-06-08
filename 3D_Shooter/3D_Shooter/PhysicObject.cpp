//
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
//

// This Include
#include "PhysicObject.h"

// Library Include
#include <cmath>

CPhysicObject::CPhysicObject(CMesh* _mesh, GLuint _textureID, GLuint _programID)
{
	this->InitializeObject(_mesh, _textureID, _programID);
}

CPhysicObject::CPhysicObject(CModel* _model, GLuint _programID)
{
	this->InitializeObject(_model, _programID);
}

CPhysicObject::~CPhysicObject()
{}

void CPhysicObject::PhysicsUpdate()
{
	// Use the velocity to move the object
	AddPosition(m_velocity);

	// Friction affecting the velocity
	m_velocity = m_velocity * m_friction;
}

float CPhysicObject::GetColliderRad() const
{
	return m_colliderRad;
}
