//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : SphereMesh.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef SPHEREMESH_H
#define SPHEREMESH_H

// Global Include
#include "Mesh.h"

class CShpereMesh : public CMesh
{
public:
	CShpereMesh();
	~CShpereMesh();

	void RenderMesh() override;

private:
	
	GLuint m_indiceCount;
};


#endif // !SPHEREMESH_H