//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : GameObject.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Local Includes
#include "Utility.h"

// Forward Declare
class CCamera;
class CMesh;

class CGameObject
{
public:
	CGameObject() = default;
	CGameObject(CMesh* _mesh, GLuint* _texture, GLuint* _program);

	void RenderObject(CCamera* _camera);

	~CGameObject();

private:

	// Member Variables
	GLuint* m_Program;
	CMesh* m_ObjMesh;
	GLuint* m_TextureID;

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	float m_Rotation;
};

#endif // !GAMEOBJECT_Hs