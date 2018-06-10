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
class CModel;

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	CGameObject(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	CGameObject(CModel* _model, GLuint _programID);
	void RenderObject(CCamera* _camera);
	void DestroyObject();
	virtual void UpdateGameObeject() {}
	virtual void OnCollision(CGameObject* _other) {}

	void AddPosition(glm::vec3 _pos);
	void AddScale(glm::vec3 _scale);
	void AddRotation(float _rotation);

	void SetPosition(glm::vec3 _pos);
	void SetPositionX(float _pos);
	void SetPositionY(float _pos);
	void SetPositionZ(float _pos);
	void SetScale(glm::vec3 _scale);
	void SetScaleX(float _scale);
	void SetScaleY(float _scale);
	void SetScaleZ(float _scale);
	void SetRotation(glm::vec3 _rotation);
	void SetRotationX(float _rotation);
	void SetRotationY(float _rotation);
	void SetRotationZ(float _rotation);

	const char* GetTag() const;
	glm::vec3 GetPosition() const;
	bool HasCollider() const;
	bool ShouldDestroyed() const;
	float GetCollisionRad() const;

	glm::vec3 GetPosistion(CGameObject* _Player) const
	{
		return(_Player->m_Position);
	}

protected:
	void InitializeObject(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	void InitializeObject(CModel* _model, GLuint _programID);

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;
	float m_ColliderRad;

	const char* m_tag;

	bool m_ShouldDestroyed;
	bool m_HasCollider;
	bool m_IsModel;

private:
	
	// Member Variables
	GLuint m_ProgramID;
	GLuint m_TextureID;

	CMesh* m_ObjMesh;
	CModel* m_ObjModel;
};

#endif // !GAMEOBJECT_H