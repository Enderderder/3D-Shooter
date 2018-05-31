//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : Mesh.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef MESH_H
#define MESH_H

#include "Utility.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

	virtual void Render() = 0;

protected:
	GLuint VAO;
};

#endif // !MESH_H
