//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Mesh.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef MESH_H
#define MESH_H

// Local Include
#include "Utility.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

	virtual void RenderMesh() = 0;

protected:
	//HEY THIS IS A CHANGE
	GLuint VAO;
};

#endif // !MESH_H
