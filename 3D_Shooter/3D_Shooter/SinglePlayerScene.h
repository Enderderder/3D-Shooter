/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SinglePlayerScene.h
// Description	:
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef SINGLEPLAYERSCENE_H
#define SINGLEPLAYERSCENE_H

// Inherited Include 
#include "Scene.h"

// Forward Declaration
enum ESCENES;
class CGameObject;
class CCamera;
class CCubeMap;
class CTextlabel;

class CSinglePlayerScene : public CScene
{
public:
	CSinglePlayerScene();
	~CSinglePlayerScene();

	// Inherited Function
	void InitialiseScene(ESCENES _eSceneNum) override;
	void RenderScene() override;
	void UpdateScene() override;

	void AddScore(int _point);
	void ChangeSwitch(int _int);

private:

	int m_GameScore;
	int m_AiSwitch;

	bool b_isfirst = false;

	CGameObject* m_player;
	CGameObject* EnemeyTemp;

	CTextLabel* m_pScore;
	CTextLabel* m_pLife;

	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::high_resolution_clock::time_point tPowerUp1;
	std::chrono::high_resolution_clock::time_point tPowerUp2;
};

#endif // !SINGLEPLAYERSCENE_H