//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
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

// Global Include
#include "TextLabel.h"
#include "Camera.h"

// Forward Declaration
enum ESCENES; 
enum ESCENES;

class CScene
{
public:
	CScene() = default;
	CScene(ESCENES _eSceneNum);
	~CScene();

	void InitialiseScene();
	void RenderScene();
	void UpdateScene();

private:
	Camera m_Camera;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	////////////////USE FOR CAMERA CLASS THEN PASSED INTO SHADERS///////////////////////////////////

	glm::mat4 m_TranslationMatrix = glm::mat4();
	glm::mat4 m_IdentityMatrix = glm::mat4();	//Defualt Matrix
	glm::mat4 m_RotationMatrix = glm::mat4();
	glm::mat4 m_ScaleMatrix = glm::mat4();
	glm::mat4 m_ModelMatrix = glm::mat4();
	glm::mat4 m_MVPMatrix = glm::mat4();

	///////////////////////////////////////////////////////////////////////////////////////////////

	const char* VertexShader;
	const char* FragmentShader;
	//std::vector<GameObject*> m_vGameObj;
	CCamera m_cCam;
};

#endif // !_SCENE_H