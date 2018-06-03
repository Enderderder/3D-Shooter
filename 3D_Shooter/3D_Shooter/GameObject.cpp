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
#include "Camera.h"
#include "ShaderLoader.h"


CGameObject::CGameObject(CMesh* _mesh, GLuint* _texture, GLuint* _program)
{
	this->InitializeObject(_mesh, _texture, _program);
}

void CGameObject::RenderObject(CCamera* _camera)
{
	glUseProgram(*m_Program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *m_TextureID);
	glUniform1i(glGetUniformLocation(*m_Program, "tex"), 0);

	glm::mat4 translate = glm::translate(glm::mat4(), m_Position);
	glm::mat4 scale = glm::scale(glm::mat4(), m_Scale);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(m_Rotation), rotationAxis);

	glm::mat4 model = translate * rotation * scale;
	GLint modelLoc = glGetUniformLocation(*m_Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat3 normalMat = glm::mat3(transpose(inverse(model)));
	GLuint normalMatLoc = glGetUniformLocation(*m_Program, "normalMat");
	glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMat));

	glm::mat4 MVP = _camera->GetProjectionMatrix() * _camera->GetViewMatrix() * model;
	GLint MVPLoc = glGetUniformLocation(*m_Program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLuint camPosLoc = glGetUniformLocation(*m_Program, "camPos");
	glUniform3fv(camPosLoc, 1, glm::value_ptr(_camera->GetCameraPosition()));

	// Render the mesh after everything is binded
	m_ObjMesh->RenderMesh();

	// Unbind the program after finishing 
	glUseProgram(0);
}

CGameObject::~CGameObject()
{}

void CGameObject::InitializeObject(CMesh * _mesh, GLuint * _texture, GLuint * _program)
{
	m_Program = _program;
	m_ObjMesh = _mesh;
	m_TextureID = _texture;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
}
