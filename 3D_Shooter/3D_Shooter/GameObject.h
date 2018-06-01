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
#include "Mesh.h"
#include "Utility.h"

// Forward Declare
class CCamera;

class CGameObject
{
public:
	CGameObject() = default;
	CGameObject(CMesh* _mesh, GLuint* _texture);

	void RenderObject(GLuint* _program, CCamera* _camera);

	~CGameObject();

private:
	CMesh* m_ObjMesh;
	GLuint* m_TextureID;

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	float m_Rotation;


};

#endif // !GAMEOBJECT_Hs