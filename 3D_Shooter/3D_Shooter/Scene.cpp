//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Scene.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// Local Include
#include "Scene.h"

// Global Include
#include "Utility.h"

//Gloabl varables
GLuint Program;
ShaderLoader ShadeL;

CScene::CScene(ESCENES _eSceneNum)
{
	/*
	
	//Main Menu
	if (_eSceneNum == 0)
	{
		//FragmentShader = "Text.fs";
		//VertexShader - "Text.vs";
	}

	//levels
	else
	{

	}

	*/

	InitialiseScene(_eSceneNum);
}

CScene::~CScene()
{

}

void CScene::InitialiseScene(ESCENES _eSceneNum)
{
	switch (_eSceneNum)
	{
	case MAINMENU:
	{
		std::vector<std::string> cubeMapPaths = {
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"back.jpg",
			"front.jpg"
		};
		m_cCubeMap = new CCubeMap(cubeMapPaths);
		break;
	}


	default: break;
	}


	//Shaders used
	//Program = ShadeL.CreateProgram(VertexShader, FragmentShader);
	//glUseProgram(Program);
}

void CScene::RenderScene()
{
	m_cCubeMap->Render(&m_cCam);


	/////////Don't know wether to use this here///////////////////////////////////////////////////

	/////////              NO. XD              ///////////////////////////////////////////////////

	/*glBindVertexArray(vao);

	GLint MVPLoc = glGetUniformLocation(Program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(m_MVPMatrix));

	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);// Get current time. 
	currentTime = currentTime / 1000.0f;  // Convert millisecond to seconds 

	GLint currentTimeLoc = glGetUniformLocation(Program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);// set value

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); //GL_POINTS, GL_LINES
	glBindVertexArray(0);*/
	
	//////////////////////////////////////////////////////////////////////////////////////////////
}

void CScene::UpdateScene()
{

}
