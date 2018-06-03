//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
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

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

//Class Pointers
CNetworkMgr m_pNetworkMgr;

void Init();
void Render();
void Update();
void ResizeWindow(int _width, int _height);
void KeyBoard_Down(unsigned char key, int x, int y);
void KeyBoard_Up(unsigned char key, int x, int y);

unsigned char KeyState[255];

int main(int argc, char **argv)
{
	// Create the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GL_MULTISAMPLE);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(util::SCR_WIDTH, util::SCR_HEIGHT);
	glutCreateWindow("3D Shooter");
	glEnable(GL_MULTISAMPLE);

	/// This Blend Func Should be Enable as the Rendering of the objects
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0, 1.0, 0.0, 1.0); // Make the background color GREEN

	glewInit();
	Init();

	

	//keyboard inputs
	glutKeyboardFunc(KeyBoard_Down);
	glutKeyboardUpFunc(KeyBoard_Up);

	//register callbacks
	glutReshapeFunc(ResizeWindow);
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	//glutPassiveMotionFunc(MousePassiveMovement);
	glutCloseFunc([]() {}); /// Modification needed

	glutMainLoop(); // Must be called last
}

void Init()
{
	CMeshMgr::GetInstance().InitialiseMeshes();


	CSceneMgr::GetInstance().Initialise();
	//Input::GetInstance()->Init();
}

void Render()
{
	CSceneMgr::GetInstance().RenderCurrentScene();
	glutSwapBuffers();

}

void Update()
{
	CSceneMgr::GetInstance().UpdateCurrentScene();

	if (KeyState[(unsigned char)'p'] == INPUT_HOLD)
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

void KeyBoard_Down(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_HOLD;
}

void KeyBoard_Up(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_RELEASED;
}