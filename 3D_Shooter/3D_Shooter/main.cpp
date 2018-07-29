/*
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
*/

// Global Include
#include "Utility.h"
#include "SceneMgr.h"
#include "SinglePlayerScene.h"
#include "MeshMgr.h"
#include "ModelMgr.h"
#include "AssetMgr.h"
#include "CNetworkMgr.h"
#include "network.h"
#include "Input.h"
#include "TextLabel.h"

// Make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

//Class Pointers
static CNetworkMgr* cNetworkMgr = CNetworkMgr::GetInstance();
static CInput* cInputMgr = CInput::GetInstance();
static CSceneMgr* cSceneMgr = CSceneMgr::GetInstance();
CTextLabel* g_FPSLabel;
CSound m_pSound;
CScene* m_pScene;

void InititializeProgram();
void Render();
void Update();
void ResizeWindow(int _width, int _height);
void UpdateFPS();

bool bIsFS;
bool bPlaySlected;
bool bMuiltplayerSlected;
bool bExitSlected;


enum MainMenu
{
	Play,
	Multiplayer,
	Exit
};

enum GameOverMenu
{
	Restart,
	GameOverMainMenu
};

enum MultiplayerMenu
{
	Host,
	Join,
	MultiMainMenu
};



MainMenu MainMenuTracker;
GameOverMenu GameOverTracker;
MultiplayerMenu MultiTracker;

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));
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
	// Initialize the Game
	InititializeProgram();

	//register callbacks
	///glutReshapeFunc(ResizeWindow);
	glutIdleFunc(Update);
	glutDisplayFunc(Render);

	glutCloseFunc([]() {
		cInputMgr->DestroyInstance();
		cSceneMgr->DestroyInstance();
		cNetworkMgr->DestroyInstance();
		CAssetMgr::GetInstance()->DestroyInstance();
		CMeshMgr::GetInstance()->DestroyInstance();
		CModelMgr::GetInstance()->DestroyInstance();
		delete g_FPSLabel;
	}); // Clean up the memory when closing the program

	glutMainLoop(); // Must be called last
}

void InititializeProgram()
{
	//m_pSound.PlaySound();
	cInputMgr->InitializeInput();
	CAssetMgr::GetInstance()->InitializeAssets();
	CMeshMgr::GetInstance()->InitializeMeshes();
	CModelMgr::GetInstance()->InitializeModels();

	//Menus Initialization
	MainMenuTracker = Play;
	GameOverTracker = Restart;
	MultiTracker = Host;

	//FPS counter starts at 0 when programs starts up
	g_FPSLabel = new CTextLabel("Arial");
	g_FPSLabel->SetPosition(glm::vec2(1305.0f, 2.0f));
	g_FPSLabel->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

	cSceneMgr->InitializeSceneMgr();
}

void Render()
{
	cSceneMgr->RenderCurrentScene();

	g_FPSLabel->RenderTextLabel();

	glutSwapBuffers();
}

void Update()
{
	// Network Main Loop
	cNetworkMgr->ServerMainLoop();
	cNetworkMgr->ClientMainLoop();

	// Update whats currently running
	cSceneMgr->UpdateCurrentScene();

	//Main Menu controls
	/*if (cSceneMgr->GetCurrentSceneEnum() == MAINMENU)
	{
		switch (MainMenuTracker)
		{
		case Play:
		{
			if (cSceneMgr->GetCurrentScene()->m_pText.size() > 1)
			{
				cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
				cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
				cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			}

			break;
		}
		case Multiplayer:
		{
			if (cSceneMgr->GetCurrentScene()->m_pText.size() > 1)
			{
				cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
				cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
				cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			}
			break;
		}
		case Exit:
		{
			if (cSceneMgr->GetCurrentScene()->m_pText.size() > 1)
			{
				cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
				cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
				cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			}
			break;
		}
		default: break;
		}

		//Up on Menu
		if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MainMenuTracker == Exit)
		{
			MainMenuTracker = Multiplayer;
			cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}
		if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MainMenuTracker == Multiplayer)
		{
			MainMenuTracker = Play;
			cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}

		//Down on Menu
		if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MainMenuTracker == Play)
		{
			MainMenuTracker = Multiplayer;
			cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		}
		if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MainMenuTracker == Multiplayer)
		{
			MainMenuTracker = Exit;
			cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;

		}

		//Enter Slection on Menu
		if(cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
			switch (MainMenuTracker)
			{
			case Play:
			{
				cSceneMgr->SwapScene(GAME);
				break;
			}
			case Multiplayer:
			{
				cSceneMgr->SwapScene(MULTIPLAYERMENU);
				break;
			}
			case Exit:
			{
				glutLeaveMainLoop();
				break;
			}
			default: break;
			}
		}
	}*/

	// In Game Controls
	if (cSceneMgr->GetCurrentSceneEnum() == GAME || cSceneMgr->GetCurrentSceneEnum() == MULTIPLAYER)
	{
		CSinglePlayerScene* thisScene = dynamic_cast<CSinglePlayerScene*>(cSceneMgr->GetCurrentScene());

		//RESTART
		if (cInputMgr->g_cKeyState[(unsigned char)'r'] == INPUT_FIRST_PRESS)
		{
			cInputMgr->g_cKeyState[(unsigned char)'r'] = INPUT_HOLD;
			std::cout << "Restarting...." << std::endl;
			cSceneMgr->SwapScene(GAME);
		}

		//MAINMENU
		if (cInputMgr->g_cKeyState[(unsigned char)27] == INPUT_FIRST_PRESS)
		{
			cInputMgr->g_cKeyState[(unsigned char)27] = INPUT_HOLD;
			std::cout << "Returning to main menu...." << std::endl;
			cSceneMgr->SwapScene(MAINMENU);
		}

		//SEEK
		if (cInputMgr->g_cKeyState[(unsigned char)'1'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(0);
		}
		//FLEE
		if (cInputMgr->g_cKeyState[(unsigned char)'2'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(1);
		}
		//PURSUE
		if (cInputMgr->g_cKeyState[(unsigned char)'3'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(2);
		}
		//WANDER
		if (cInputMgr->g_cKeyState[(unsigned char)'4'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(3);
		}
		//LEADERFOLLOW
		if (cInputMgr->g_cKeyState[(unsigned char)'5'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(4);
		}
		//ARRIVE
		if (cInputMgr->g_cKeyState[(unsigned char)'6'] == INPUT_FIRST_PRESS)
		{
			thisScene->ChangeSwitch(5);
		}
	}

	if (cSceneMgr->GetCurrentSceneEnum() == GAMEOVER)
	{
		switch (GameOverTracker)
		{
		case Restart:
		{
			cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			break;
		}
		case GameOverMainMenu:
		{
			cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			break;
		}
		default:
			break;
		}

		if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && GameOverTracker == GameOverMainMenu)
		{
			cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
			GameOverTracker = Restart;
		}

		if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && GameOverTracker == Restart)
		{
			cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
			GameOverTracker = GameOverMainMenu;
		}
		
		if (cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;

			switch (GameOverTracker)
			{
			case Restart:
			{
				cSceneMgr->SwapScene(GAME);
				
				break;
			}
				
			case GameOverMainMenu:
			{
				cSceneMgr->SwapScene(MAINMENU);
				
				break;
			}
				
			default:
				break;
			}
		}
	}

	//MULTIPLAYER Menu Functionlity
	if (cSceneMgr->GetCurrentSceneEnum() == MULTIPLAYERMENU)
	{
		switch (MultiTracker)
		{
		case Host:
		{
			cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			break;
		}
		case Join:
		{
			cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			break;
		}
		case MultiMainMenu:
		{
			cSceneMgr->GetCurrentScene()->m_pText[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[2]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			break;
		}
		default:
			break;
		}

		//Up on Menu
		if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MultiTracker == MultiMainMenu)
		{
			MultiTracker = Join;
			cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}
		if (cInputMgr->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MultiTracker == Join)
		{
			MultiTracker = Host;
			cInputMgr->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}

		//Down on Menu
		if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MultiTracker == Host)
		{
			MultiTracker = Join;
			cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		}

		if (cInputMgr->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MultiTracker == Join)
		{
			MultiTracker = MultiMainMenu;
			cInputMgr->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;

		}

		if (cInputMgr->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			switch (MultiTracker)
			{
			case Host:
			{
				cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				cNetworkMgr->StartNetwork(SERVER);
				cSceneMgr->SwapScene(LOBBY);
			}
				break;
			case Join:
			{
				cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				cNetworkMgr->StartNetwork(CLIENT);
				cSceneMgr->SwapScene(LOBBY);
			}
				break;
			case MultiMainMenu:
			{
				cInputMgr->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				cSceneMgr->SwapScene(MAINMENU);
			}
				break;
			default:
				break;
			}


		}


	}


	/// Debug: Goes Straight to Game Over Scene ===============================
	if (cInputMgr->g_cKeyState[(unsigned char)'e'] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)'e'] = INPUT_HOLD;
		cSceneMgr->SwapScene(GAMEOVER);
	}
	/// =======================================================================

	// Full Screen Control
	if (cInputMgr->g_cKeyState[(unsigned char)'f'] == INPUT_FIRST_PRESS)
	{
		cInputMgr->g_cKeyState[(unsigned char)'f'] = INPUT_HOLD;
		glutFullScreenToggle();
	}

	UpdateFPS();

	// Goes To Render
	glutPostRedisplay();
}

void ResizeWindow(int _width, int _height)
{
	glutReshapeWindow(util::SCR_WIDTH, util::SCR_HEIGHT);
}

void UpdateFPS()
{
	static float framesPerSecond = 0.0f;	// This will store our fps
	static float lastTime = 0.0f;			// This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime >= 1.0f)
	{
		lastTime = currentTime;

		std::ostringstream iConvert;
		iConvert << framesPerSecond;
		g_FPSLabel->SetText(iConvert.str());

		framesPerSecond = 0;
	}
}