//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : GameObject.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "GameObject.h"

// Local Include
#include "MeshMgr.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "ShaderLoader.h"

CGameObject::CGameObject(CMesh* _mesh, GLuint _textureID, GLuint _programID) :
	m_IsModel(false),
	m_ObjModel(nullptr)
{
	InitializeObject(_mesh, _textureID, _programID);
}

CGameObject::CGameObject(CModel* _model, GLuint _programID) :
	m_IsModel(true),
	m_ObjMesh(nullptr)
{
	InitializeObject(_model, _programID);
}

void CGameObject::RenderObject(CCamera* _camera)
{
	glUseProgram(m_ProgramID);

	glm::mat4 translate = glm::translate(glm::mat4(), m_Position);
	glm::mat4 scale = glm::scale(glm::mat4(), m_Scale);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 model = translate * rotation * scale;
	glm::mat4 mvp = _camera->GetProjectionMatrix() *  _camera->GetViewMatrix() * model;
	GLint mvpLoc = glGetUniformLocation(m_ProgramID, "MVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	GLint modelLoc = glGetUniformLocation(m_ProgramID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat3 normalMat = glm::mat3(transpose(inverse(model)));
	GLuint normalMatLoc = glGetUniformLocation(m_ProgramID, "normalMat");
	glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMat));

	GLuint camPosLoc = glGetUniformLocation(m_ProgramID, "camPos");
	glUniform3fv(camPosLoc, 1, glm::value_ptr(_camera->GetCameraPosition()));

	if (m_IsModel)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		// Render the model
		m_ObjModel->Render(_camera, this->m_ProgramID);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glUniform1i(glGetUniformLocation(m_ProgramID, "tex"), 0);

		// Render the mesh after everything is binded
		m_ObjMesh->RenderMesh();
	}

	// Unbind the program after finishing 
	glUseProgram(0);
}

void CGameObject::DestroyObject()
{
	this->m_ShouldDestroyed = true;
}

CGameObject::CGameObject()
{
	this->m_HasCollider = false;
	this->m_ShouldDestroyed = false;
}

CGameObject::~CGameObject()
{}

void CGameObject::InitializeObject(CMesh * _mesh, GLuint _textureID, GLuint _programID)
{
	m_ProgramID = _programID;
	m_TextureID = _textureID;
	m_ObjMesh = _mesh;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Rotation = glm::vec3();
}

void CGameObject::InitializeObject(CModel* _model, GLuint _programID)
{
	m_ProgramID = _programID;
	m_ObjModel = _model;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Rotation = glm::vec3();
}

void CGameObject::AddPosition(glm::vec3 _pos)
{
	m_Position += _pos;
}

void CGameObject::AddScale(glm::vec3 _scale)
{
	m_Scale += _scale;
}

void CGameObject::AddRotation(float _rotation)
{
	m_Rotation += _rotation;
}

void CGameObject::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;
}

void CGameObject::SetPositionX(float _pos)
{
	m_Position.x = _pos;
}

void CGameObject::SetPositionY(float _pos)
{
	m_Position.y = _pos;
}

void CGameObject::SetPositionZ(float _pos)
{
	m_Position.z = _pos;
}

void CGameObject::SetScale(glm::vec3 _scale)
{
	m_Scale = _scale;
}

void CGameObject::SetScaleX(float _scale)
{
	m_Scale.x = _scale;
}

void CGameObject::SetScaleY(float _scale)
{
	m_Scale.y = _scale;
}

void CGameObject::SetScaleZ(float _scale)
{
	m_Scale.z = _scale;
}

void CGameObject::SetRotation(glm::vec3 _rotation)
{
	m_Rotation = _rotation;
}

void CGameObject::SetRotationX(float _rotation)
{
	m_Rotation.x = _rotation;
}

void CGameObject::SetRotationY(float _rotation)
{
	m_Rotation.y = _rotation;
}

void CGameObject::SetRotationZ(float _rotation)
{
	m_Rotation.z = _rotation;
}

bool CGameObject::HasCollider() const
{
	return m_HasCollider;
}

bool CGameObject::ShouldDestroyed() const
{
	return m_ShouldDestroyed;
}

float CGameObject::GetCollisionRad() const
{
	return m_ColliderRad;
}

const char* CGameObject::GetTag() const
{
	return m_tag;
}

glm::vec3 CGameObject::GetPosition() const
{
	return m_Position;
}
