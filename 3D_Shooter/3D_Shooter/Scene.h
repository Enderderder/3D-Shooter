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

// OpenGL Include
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>

// Library Include
#include <vector>
#include <chrono>
#include <memory>

// Forward Declaration
enum ESCENES;
class CGameObject;
class CCamera;
class CCubeMap;
class CTextLabel;

class CScene
{
public:
	CScene();
	CScene(ESCENES _eSceneNum);
	~CScene();

	virtual void InitialiseScene(ESCENES _eSceneNum);
	virtual void RenderScene();
	virtual void UpdateScene();

	void CheckCollision();

	void Instantiate(CGameObject* _gameobj);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
	void DestroyObject(CGameObject* _gameobj);

	std::vector<CGameObject*> GetObjectVec() const;
	

	CTextLabel* TextTemp;
	std::vector< CTextLabel* > m_pText;

protected:
	ESCENES m_pCurrentEnum;

	CCamera* m_MainCamera;

	CCubeMap * m_cCubeMap;

	std::vector<CGameObject*> m_vGameObj;

	std::vector< std::shared_ptr<CTextLabel> > m_vTextLabel;

private:

	//std::vector<CGameObject*> m_vGameObj;
	
	//CCamera* m_MainCamera;
	//CCubeMap* m_cCubeMap;
	//ESCENES m_pCurrentEnum;
};

#endif // !SCENE_H