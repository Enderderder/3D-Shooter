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

CPhysicObject::CPhysicObject(CMesh* _mesh, GLuint _textureID, GLuint _programID)
{
	this->InitializeObject(_mesh, _textureID, _programID);
}

CPhysicObject::CPhysicObject(CModel* _model, GLuint _programID)
{
	this->InitializeObject(_model, _programID);
}


CPhysicObject::~CPhysicObject()
{
}
