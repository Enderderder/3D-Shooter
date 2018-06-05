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

// Global Includes
#include "Utility.h"

// Forward Declare
class CCamera;
class CMesh;

class CGameObject
{
public:
	CGameObject() = default;
	~CGameObject();

	CGameObject(CMesh* _mesh, GLuint* _texture, GLuint* _program);
	void RenderObject(CCamera* _camera);
	virtual void UpdateGameObeject() {}

	void AddPosition(glm::vec3 _pos);
	void AddScale(glm::vec3 _scale);
	void AddRotation(float _rotation);

	void SetPosition(glm::vec3 _pos);
	void SetScale(glm::vec3 _scale);
	void SetRotation(float _rotation);

protected:
	void InitializeObject(CMesh* _mesh, GLuint* _texture, GLuint* _program);

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	float m_Rotation;

private:

	// Member Variables
	GLuint* m_Program;
	CMesh* m_ObjMesh;
	GLuint* m_TextureID;
};

#endif // !GAMEOBJECT_H