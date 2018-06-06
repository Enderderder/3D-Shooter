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
#include "ModelMgr.h"
#include "CNetworkMgr.h"
#include "Input.h"


// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

//Class Pointers
CNetworkMgr m_pNetworkMgr;
CInput* cInput = CInput::GetInstance();
CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();
TextLabel* m_pTextLabel;

void InititializeProgram();
void Render();
void Update();
void ResizeWindow(int _width, int _height);
void FPSCounter();

bool bIsFS;

int main(int argc, char **argv)
{
	
	bIsFS = false;
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
	//glutReshapeFunc(ResizeWindow);
	glutDisplayFunc(Render);
	
	glutIdleFunc(Update);

	glutCloseFunc([]() {
		cInput->DestroyInstance();
		cSceneMgr->DestroyInstance();
		CMeshMgr::GetInstance().DestroyInstance();
		CModelMgr::GetInstance().DestroyInstance();
	}); // Clean up the memory when closing the program

	glutMainLoop(); // Must be called last
}

void InititializeProgram()
{
	cInput->InitializeInput();
	CMeshMgr::GetInstance().InitializeMeshes();
	CModelMgr::GetInstance().InitializeModels();

	//FPS counter starts at 0 when programs starts up
	m_pTextLabel = new TextLabel("0", "Resources/fonts/arial.ttf", glm::vec2(1305.0f, 2.0f));
	m_pTextLabel->SetScale(1.0f);
	m_pTextLabel->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));
	
	cSceneMgr->InitializeSceneMgr();
}

void Render()
{
	cSceneMgr->RenderCurrentScene();

	FPSCounter();
	m_pTextLabel->Render();
	
	glutSwapBuffers();
}

void Update()
{
	

	cSceneMgr->UpdateCurrentScene();

	if (cInput->g_cKeyState[(unsigned char)'p'] == INPUT_FIRST_PRESS)
	{
		std::thread Thread_obj1(&CNetworkMgr::StartNetwork, &m_pNetworkMgr);
		
		Thread_obj1.join();
	}

	if (cInput->g_cKeyState[(unsigned char)'f'] == INPUT_FIRST_PRESS && bIsFS == false)
	{
		glutFullScreenToggle();
		bIsFS = true;
	}
	if (cInput->g_cKeyState[(unsigned char)'f'] == INPUT_RELEASED && bIsFS == true)
	{
		bIsFS = false;
	}

	

	glutPostRedisplay();
}

void ResizeWindow(int _width, int _height)
{
	glutReshapeWindow(util::SCR_WIDTH, util::SCR_HEIGHT);
}

void FPSCounter()
{
	static float framesPerSecond = 0.0f;       // This will store our fps
	static float lastTime = 0.0f;       // This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;

		std::ostringstream iConvert;
		iConvert << framesPerSecond;
		m_pTextLabel->SetText(iConvert.str());

		framesPerSecond = 0;
	}

}