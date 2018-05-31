//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CubeMap.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef CUBEMAP_H
#define CUBEMAP_H

// OpenGL Library Include
#include <glew.h>
#include <freeglut.h>

// Library Include 
#include <string>
#include <vector>

// Forward Declare
class CCamera;

class CCubeMap
{
public:
	CCubeMap() = default;
	CCubeMap(std::vector<std::string> _textureFilePaths);
	~CCubeMap();

	void Render(CCamera* _camera);

	GLuint GetTextureID() const;

private:
	GLuint m_program;
	GLuint VAO;

	GLuint textureID;
};

#endif // !CUBEMAP_H