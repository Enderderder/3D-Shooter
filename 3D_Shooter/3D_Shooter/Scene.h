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

#ifndef _SCENE_H
#define _SCENE_H

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

	void Instantiate(CGameObject* _gameobj);

private:
  
	std::vector<CGameObject*> m_vGameObj;
	CCamera* m_cCam;
	CCubeMap* m_cCubeMap;
};

#endif // !_SCENE_H