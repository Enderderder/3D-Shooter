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
#include "AssetMgr.h"
#include "CNetworkMgr.h"
#include "Input.h"


// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

//Class Pointers
CNetworkMgr m_pNetworkMgr;
static CInput* cInput = CInput::GetInstance();
static CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();
TextLabel* m_pTextLabel;
CSound m_pSound;

void InititializeProgram();
void Render();
void Update();
void ResizeWindow(int _width, int _height);
void FPSCounter();

bool bIsFS;

int main(int argc, char **argv)
{
	srand(time(NULL));
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
		cInput->DestroyObject();
		cSceneMgr->DestroyObject();
		CAssetMgr::GetInstance()->DestroyInstance();
		CMeshMgr::GetInstance()->DestroyInstance();
		CModelMgr::GetInstance()->DestroyInstance();
		delete m_pTextLabel;
	}); // Clean up the memory when closing the program

	glutMainLoop(); // Must be called last
}

void InititializeProgram()
{
	//m_pSound.PlaySound();
	cInput->InitializeInput();
	CAssetMgr::GetInstance()->InitializeAssets();
	CMeshMgr::GetInstance()->InitializeMeshes();
	CModelMgr::GetInstance()->InitializeModels();

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

	// Update whats currently running
	cSceneMgr->UpdateCurrentScene();
	//Main Menu controls
	if (cSceneMgr->GetCurrentSceneEnum() == MAINMENU)
	{
		if (cInput->g_cKeyState[(unsigned char)'p'] == INPUT_FIRST_PRESS)
		{
			std::cout << "Loading...." << std::endl;
			cSceneMgr->SwapScene(GAME);
		}

		if (cInput->g_cKeyState[(unsigned char)27] == INPUT_FIRST_PRESS)
		{
			glutLeaveMainLoop();
		}
	}

	if (cSceneMgr->GetCurrentSceneEnum() == GAME)
	{
		//RESTART
		if (cInput->g_cKeyState[(unsigned char)'r'] == INPUT_FIRST_PRESS)
		{
			std::cout << "Restarting...." << std::endl;
			cSceneMgr->SwapScene(GAME);
		}

		//SEEK
		if (cInput->g_cKeyState[(unsigned char)'1'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(0);
		}
		//FLEE
		if (cInput->g_cKeyState[(unsigned char)'2'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(1);
		}
		//PURSUE
		if (cInput->g_cKeyState[(unsigned char)'3'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(2);
		}
		//WANDER
		if (cInput->g_cKeyState[(unsigned char)'4'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(3);
		}
		//LEADERFOLLOW
		if (cInput->g_cKeyState[(unsigned char)'5'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(4);
		}
		//ARRIVE
		if (cInput->g_cKeyState[(unsigned char)'6'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->GetCurrentScene()->ChangeSwitch(5);
		}
	}

	if (cSceneMgr->GetCurrentSceneEnum() == GAMEOVER)
	{
		if (cInput->g_cKeyState[(unsigned char)'r'] == INPUT_FIRST_PRESS)
		{
			std::cout << "Loading...." << std::endl;
			cSceneMgr->SwapScene(GAME);
		}

		if (cInput->g_cKeyState[(unsigned char)'e'] == INPUT_FIRST_PRESS)
		{
			cSceneMgr->SwapScene(MAINMENU);
		}

	}

	if (cInput->g_cKeyState[(unsigned char)'h'] == INPUT_FIRST_PRESS && bIsFS == false)
	{
		m_pNetworkMgr.StartNetwork();
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
	static float framesPerSecond = 0.0f;	// This will store our fps
	static float lastTime = 0.0f;			// This will hold the time from the last frame
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