

// Local Include
#include "Scene.h"

// Global Include
#include "Utility.h"

//Gloabl varables
GLuint Program;
ShaderLoader ShadeL;

CScene::CScene(ESCENES _eSceneNum)
{
	//Main Menu
	if (_eSceneNum == 0)
	{
		FragmentShader = "Text.fs";
		VertexShader - "Text.vs";
	}

	//levels
	else
	{

	}
	
}

CScene::~CScene()
{

}

void CScene::InitialiseScene()
{
	//Shaders used
	Program = ShadeL.CreateProgram(VertexShader, FragmentShader);
	glUseProgram(Program);
}

void CScene::RenderScene()
{

}

void CScene::UpdateScene()
{

}
