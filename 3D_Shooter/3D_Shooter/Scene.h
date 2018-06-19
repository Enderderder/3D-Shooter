//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Scene.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef SCENE_H
#define SCENE_H

// Library Include
#include <vector>
#include <chrono>

// Local Include
#include "TextLabel.h"
#include "CubeMap.h"

// Forward Declaration
enum ESCENES;
class CGameObject;
class CCamera;

class CScene
{
public:
	CScene() = default;
	CScene(ESCENES _eSceneNum);
	~CScene();

	void InitialiseScene(ESCENES _eSceneNum);
	void RenderScene();
	void UpdateScene();
	void CheckCollision();

	void Instantiate(CGameObject* _gameobj);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
	void DestroyObject(CGameObject* _gameobj);

	void AddScore(int _point);
	void ChangeSwitch(int _int);

	std::vector<CGameObject*> GetObjectVec() const;
	std::vector<CTextLabel*> m_pText;

private:

	int m_GameScore;
	int m_AiSwitch;
	CGameObject* EnemeyTemp = nullptr;
	bool b_isfirst = false;
  
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::high_resolution_clock::time_point tPowerUp1;
	std::chrono::high_resolution_clock::time_point tPowerUp2;

	std::vector<CGameObject*> m_vGameObj;
	
	CCamera* m_cCam;
	CCubeMap* m_cCubeMap;
	ESCENES m_pCurrentEnum;
	CGameObject* m_player;
	
	CTextLabel* m_pScore = new CTextLabel("Arial", "Score: 0", glm::vec2(1000.0f, 700.0f));
	CTextLabel* m_pLife = new CTextLabel("Arial", "Life: 0", glm::vec2(0.0f, 700.0f));
};

#endif // !SCENE_H