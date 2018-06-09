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
	ESCENES GetCurrentEnum();
	void DestroyObject(CGameObject* _gameobj);

private:
  
	std::vector<CGameObject*> m_vGameObj;
	std::vector<TextLabel*> m_pText;
	CCamera* m_cCam;
	CCubeMap* m_cCubeMap;
	ESCENES m_pCurrentEnum;
	CGameObject* m_player;
};

#endif // !SCENE_H