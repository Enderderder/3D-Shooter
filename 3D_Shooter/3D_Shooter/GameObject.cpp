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

// Temp
static ShaderLoader sloader;

CGameObject::CGameObject(CMesh* _mesh, GLuint* _texture, GLuint* _program)
{

	m_Program = _program;
	m_ObjMesh = _mesh;
	m_TextureID = _texture;
	
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	
	
	//tempProgram = sloader.CreateProgram("Shaders/DiffuseLight.vs", "Shaders/DiffuseLight.fs");

	//glGenTextures(1, &tempTexture);
	//glBindTexture(GL_TEXTURE_2D, tempTexture);

	//int width, height;
	//unsigned char* image = SOIL_load_image(
	//	"Resources/Textures/TITANFALL.jpg",	// File path / Name
	//	&width,								// Output for the image width
	//	&height,							// Output for the image height
	//	0,									// Output for number of channels
	//	SOIL_LOAD_RGBA);					// Load RGB values only

	//glTexImage2D(
	//	GL_TEXTURE_2D,		// Type of texture
	//	0,					// Mipmap level, 0 for base
	//	GL_RGBA,			// Number of color components in texture
	//	width,				// Width of the texture
	//	height,				// Height of the texture
	//	0,					// This value must be 0
	//	GL_RGBA,			// Format for the pixel data
	//	GL_UNSIGNED_BYTE,	// Data type for the pixel data
	//	image);				// Pointer to image data in memory

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void CGameObject::RenderObject(CCamera* _camera)
{
	/*glUseProgram(tempProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tempTexture);

	glUniform1i(glGetUniformLocation(tempProgram, "tex"), 0);

	glm::mat4 translate = glm::translate(glm::mat4(), m_Position);

	glm::mat4 scale = glm::scale(glm::mat4(), m_Scale);

	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(m_Rotation), rotationAxis);

	glm::mat4 model = translate * rotation * scale;
	GLint modelLoc = glGetUniformLocation(tempProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 MVP = _camera->GetProjectionMatrix() * _camera->GetViewMatrix() * model;
	GLint MVPLoc = glGetUniformLocation(tempProgram, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLuint camPosLoc = glGetUniformLocation(tempProgram, "camPos");
	glUniform3fv(camPosLoc, 1, glm::value_ptr(_camera->GetCameraPosition()));

	tempMesh.RenderMesh();

	glUseProgram(0);*/

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
