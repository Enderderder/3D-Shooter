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

void Init();
void Render();
void Update();
void ResizeWindow(int _width, int _height);

int main(int argc, char **argv)
{
	// Create the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GL_MULTISAMPLE);
	glutInitWindowPosition(150, 200);
	glutInitWindowSize(util::SCR_WIDTH, util::SCR_HEIGHT);
	glutCreateWindow("3D Shooter");
	glEnable(GL_MULTISAMPLE);

	/// This Blend Func Should be Enable as the Rendering of the objects
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0, 1.0, 0.0, 1.0); // Make the background color GREEN

	glewInit();
	Init();

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
	glutPostRedisplay();
}

void ResizeWindow(int _width, int _height)
{
	glutReshapeWindow(util::SCR_WIDTH, util::SCR_HEIGHT);
}