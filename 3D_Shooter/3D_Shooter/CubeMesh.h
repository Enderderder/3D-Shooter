//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : CubeMesh.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "Utility.h"

class CCubeMesh
{
public:
	CCubeMesh();
	~CCubeMesh();

	void Render();
	
private:

	GLuint VAO;
};

#endif // !CUBEMESH_H