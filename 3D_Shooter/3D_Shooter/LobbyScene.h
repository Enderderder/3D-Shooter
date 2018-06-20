/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : LobbyScene.h
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef LOBBYSCENE_H
#define LOBBYSCENE_H

// Inherited Include
#include "Scene.h"

// Forward Declaration
enum ESCENES;
class CGameObject;
class CCamera;
class CCubeMap;

class CLobbyScene : public CScene
{
public:
	CLobbyScene();
	~CLobbyScene();

	// Inherited Function
	void InitialiseScene(ESCENES _eSceneNum) override;
	void RenderScene() override;
	void UpdateScene() override;

private:

	// Private Member Function
	void MenuControl();
};

#endif // !LOBBYSCENE_H