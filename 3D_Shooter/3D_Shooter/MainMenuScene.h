//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : MainMenuScene.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

// Inherited Include
#include "Scene.h"

// Enum Declare
enum MAINMENUBUTTON
{
	Play,
	Multiplayer,
	Exit
};

// Forward Declaration
enum ESCENES;

class CMainMenuScene : public CScene
{
public:
	CMainMenuScene();
	~CMainMenuScene();

	// Inherited Function
	void InitialiseScene(ESCENES _eSceneNum) override;
	void RenderScene() override;
	void UpdateScene() override;

private:

	// Private Member Function
	void MenuControl();
	void ChangeSelection(MAINMENUBUTTON);

	// Member Variable
	MAINMENUBUTTON m_MainMenuTracker;

	// Menu Text
	std::shared_ptr< CTextLabel > m_tSinglePlayer;
	std::shared_ptr< CTextLabel > m_tMultiPlayer;
	std::shared_ptr< CTextLabel > m_tExitGame;
};

#endif // !MAINMENUSCENE_H