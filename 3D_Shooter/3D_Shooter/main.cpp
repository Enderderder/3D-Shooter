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

enum Lobby
{
	StartGame,
	LobbyMainMenu
};

MainMenu MainMenuTracker;
GameOverMenu GameOverTracker;
MultiplayerMenu MultiTracker;
Lobby LobbyTracker;

int main(int argc, char **argv)
{
	srand(time(NULL));
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

	//Menus Initialization
	MainMenuTracker = Play;
	GameOverTracker = Restart;
	MultiTracker = Host;
	LobbyTracker = StartGame;

	//FPS counter starts at 0 when programs starts up
	m_pTextLabel = new TextLabel("0", "Resources/fonts/arial.ttf", glm::vec2(1305.0f, 2.0f));
	m_pTextLabel->SetScale(1.0f);
	m_pTextLabel->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

	cSceneMgr->InitializeSceneMgr();
}

void Render()
{
	cSceneMgr->RenderCurrentScene();

	m_pTextLabel->Render();

	glutSwapBuffers();
}

void Update()
{
	// Network Main Loop
	m_pNetworkMgr.ServerMainLoop();

	// Update whats currently running
	cSceneMgr->UpdateCurrentScene();

	//Main Menu controls
	if (cSceneMgr->GetCurrentSceneEnum() == MAINMENU)
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
		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MainMenuTracker == Exit)
		{
			MainMenuTracker = Multiplayer;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}
		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MainMenuTracker == Multiplayer)
		{
			MainMenuTracker = Play;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}

		//Down on Menu
		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MainMenuTracker == Play)
		{
			MainMenuTracker = Multiplayer;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		}
		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MainMenuTracker == Multiplayer)
		{
			MainMenuTracker = Exit;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;

		}

		//Enter Slection on Menu
		if(cInput->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			cInput->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
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

		//Start Network
		if (cInput->g_cKeyState[(unsigned char)'h'] == INPUT_FIRST_PRESS && !m_pNetworkMgr.IsNetOnline())
		{
			cInput->g_cKeyState[(unsigned char)'h'] = INPUT_HOLD;

			std::cout << "Starting the Network..." << std::endl;
			m_pNetworkMgr.StartNetwork();
		}
	}

	// In Game Controls
	if (cSceneMgr->GetCurrentSceneEnum() == GAME || cSceneMgr->GetCurrentSceneEnum() == MULTIPLAYER)
	{
		//RESTART
		if (cInput->g_cKeyState[(unsigned char)'r'] == INPUT_FIRST_PRESS)
		{
			std::cout << "Restarting...." << std::endl;
			cSceneMgr->SwapScene(GAME);
		}

		//MAINMENU
		if (cInput->g_cKeyState[(unsigned char)27] == INPUT_FIRST_PRESS)
		{
			std::cout << "Returning to main menu...." << std::endl;
			cSceneMgr->SwapScene(MAINMENU);
			cInput->g_cKeyState[(unsigned char)27] == INPUT_RELEASED;
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

		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && GameOverTracker == GameOverMainMenu)
		{
			GameOverTracker = Restart;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_RELEASED;
		}

		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && GameOverTracker == Restart)
		{
			GameOverTracker = GameOverMainMenu;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_RELEASED;
		}
		
		if (cInput->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{


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

			cInput->g_cKeyState[(unsigned char)' '] == INPUT_RELEASED;
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
		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MultiTracker == MultiMainMenu)
		{
			MultiTracker = Join;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}
		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && MultiTracker == Join)
		{
			MultiTracker = Host;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_HOLD;
		}

		//Down on Menu
		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MultiTracker == Host)
		{
			MultiTracker = Join;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;
		}

		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && MultiTracker == Join)
		{
			MultiTracker = MultiMainMenu;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_HOLD;

		}

		if (cInput->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			switch (MultiTracker)
			{
			case Host:
			{
				cInput->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				m_pNetworkMgr.StartNetwork();
				cSceneMgr->SwapScene(LOBBY);
			}
				break;
			case Join:
			{
				cInput->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				m_pNetworkMgr.StartNetwork();
				cSceneMgr->SwapScene(LOBBY);
			}
				break;
			case MultiMainMenu:
			{
				cInput->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				cSceneMgr->SwapScene(MAINMENU);
			}
				break;
			default:
				break;
			}


		}


	}
	//LOBBY Menu Functionlity
	if (cSceneMgr->GetCurrentSceneEnum() == LOBBY)
	{
		switch (LobbyTracker)
		{
		case StartGame:
		{
			cSceneMgr->GetCurrentScene()->m_pText[4]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			cSceneMgr->GetCurrentScene()->m_pText[5]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			break;
		}
		case LobbyMainMenu:
		{
			cSceneMgr->GetCurrentScene()->m_pText[4]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			cSceneMgr->GetCurrentScene()->m_pText[5]->SetColor(glm::vec3(1.0f, 0.0f, 0.5f));
			break;
		}
		default:
			break;
		}

		if (cInput->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS && LobbyTracker == LobbyMainMenu)
		{
			LobbyTracker = StartGame;
			cInput->g_cKeyState[(unsigned char)'w'] = INPUT_RELEASED;
		}

		if (cInput->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS && LobbyTracker == StartGame)
		{
			LobbyTracker = LobbyMainMenu;
			cInput->g_cKeyState[(unsigned char)'s'] = INPUT_RELEASED;
		}

		if (cInput->g_cKeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
		{
			switch (LobbyTracker)
			{
			case StartGame:
			{
				cInput->g_cKeyState[(unsigned char)' '] == INPUT_HOLD;

			}
				break;
			case LobbyMainMenu:
			{
				cInput->g_cKeyState[(unsigned char)' '] = INPUT_HOLD;
				cSceneMgr->SwapScene(MAINMENU);
			}
				break;
			default:
				break;
			}
		}
	}

	/// Debug: Goes Straight to Game Over Scene ===============================
	if (cInput->g_cKeyState[(unsigned char)'e'] == INPUT_FIRST_PRESS)
	{
		cSceneMgr->SwapScene(GAMEOVER);

	}
	/// =======================================================================

	// Full Screen Control
	if (cInput->g_cKeyState[(unsigned char)'f'] == INPUT_FIRST_PRESS)
	{
		cInput->g_cKeyState[(unsigned char)'f'] = INPUT_HOLD;
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
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;

		std::ostringstream iConvert;
		iConvert << framesPerSecond;
		m_pTextLabel->SetText(iConvert.str());

		framesPerSecond = 0;
	}
}