//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : main.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// Global Include
#include "Utility.h"
#include "SceneMgr.h"
#include "MeshMgr.h"
#include "CNetworkMgr.h"
#include "Input.h"

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

//Class Pointers
CNetworkMgr m_pNetworkMgr;
CInput* cInput = CInput::GetInstance();
CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();

void InititializeProgram();
void Render();
void Update();
void ResizeWindow(int _width, int _height);

int main(int argc, char **argv)
{
	// Create the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GL_MULTISAMPLE);
	glutInitWindowPosition(400, 200);

	glutInitWindowSize(util::SCR_WIDTH, util::SCR_HEIGHT);
	glutCreateWindow("3D Shooter");
	glEnable(GL_MULTISAMPLE);

	// Set Clear Screen Color
	glClearColor(0.0, 1.0, 0.0, 1.0); // Make the background color GREEN

	// Initialize OpenGL Library
	glewInit();

	InititializeProgram();

	//register callbacks
	glutReshapeFunc(ResizeWindow);
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutCloseFunc([]() {}); /// Modification needed

	glutMainLoop(); // Must be called last
}

void InititializeProgram()
{
	cInput->InitializeInput();
	CMeshMgr::GetInstance().InitializeMeshes();

	cSceneMgr->InitializeSceneMgr();
}

void Render()
{
	cSceneMgr->RenderCurrentScene();

	glutSwapBuffers();

}

void Update()
{
	cSceneMgr->UpdateCurrentScene();

	if (cInput->g_cKeyState[(unsigned char)'p'] == INPUT_HOLD)
	{

		std::thread Thread_obj1(&CNetworkMgr::StartNetwork, &m_pNetworkMgr);
		
		Thread_obj1.join();
	}

	glutPostRedisplay();
}

void ResizeWindow(int _width, int _height)
{
	glutReshapeWindow(util::SCR_WIDTH, util::SCR_HEIGHT);
}