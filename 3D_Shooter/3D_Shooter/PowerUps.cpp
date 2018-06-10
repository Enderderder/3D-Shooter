//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : PowerUps.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "PowerUps.h"

// Local Include
#include "MeshMgr.h"
#include "AssetMgr.h"
#include "MeshMgr.h"
#include "Mesh.h"
#include "Camera.h"
#include "CubeMap.h"

CPowerUps::CPowerUps(EPOWERUPEFFECT _effect) :
	m_effect(_effect)
{
	switch (_effect)
	{
	case HEAL:
		m_rimColor = glm::vec3(1.0f, 1.0f, 0.0f);
		break;
	case SCORE:
		m_rimColor = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case MOVESPD:
		m_rimColor = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case ATKSPD:
		break;
	default:
		break;
	}
	m_tag = "PowerUp";
	m_HasCollider = true;
	m_ColliderRad = 0.5f;
	m_Scale = glm::vec3(0.5f, 0.5f, 0.5f);

	m_IsModel = false;
	InitializeObject(CMeshMgr::GetInstance()->GetMesh(SPHERE),
		CAssetMgr::GetInstance()->GetTextureID("Bullet"),
		CAssetMgr::GetInstance()->GetProgramID("ReflectRim"));

	m_cubeMapTex = CMeshMgr::GetInstance()->GetCubeMap(GAMECUBEMAP);
}

CPowerUps::~CPowerUps()
{}

void CPowerUps::RenderObject(CCamera* _camera)
{
	glUseProgram(m_ProgramID);

	glm::mat4 translate = glm::translate(glm::mat4(), m_Position);
	glm::mat4 scale = glm::scale(glm::mat4(), m_Scale);
	glm::mat4 rotation = glm::mat4();
	rotation = glm::rotate(rotation, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
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

	GLuint rimColorLoc = glGetUniformLocation(m_ProgramID, "rimColor");
	glUniform3fv(rimColorLoc, 1, glm::value_ptr(m_rimColor));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glUniform1i(glGetUniformLocation(m_ProgramID, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTex->GetTextureID());
	glUniform1i(glGetUniformLocation(m_ProgramID, "cubeMap"), 1);

	// Render the mesh
	m_ObjMesh->RenderMesh();

	// Unbind the program after finishing 
	glUseProgram(0);
}

void CPowerUps::OnCollision(CGameObject* _other)
{
	if (_other->GetTag() == "Player")
	{
		DestroyObject();
	}
}

EPOWERUPEFFECT CPowerUps::GetEffect() const
{
	return m_effect;
}
