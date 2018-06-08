//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : PhysicObject.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

// Inherited Include
#include "GameObject.h"

class CPhysicObject : public CGameObject
{
public:
	CPhysicObject() = default;
	CPhysicObject(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	CPhysicObject(CModel* _model, GLuint _programID);
	~CPhysicObject();

	void PhysicsUpdate();

protected:

	glm::vec3 m_directionVec;
	glm::vec3 m_velocity;
	float m_friction;

	float m_colliderRad;
};

#endif // !PHYSICOBJECT_H