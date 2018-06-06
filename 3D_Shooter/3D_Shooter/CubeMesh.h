//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CubeMesh.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef CUBEMESH_H
#define CUBEMESH_H

// Inherited include
#include "Mesh.h"

// Local Include
//#include "Utility.h"

class CCubeMesh : public CMesh
{
public:
	CCubeMesh();
	~CCubeMesh();

	void RenderMesh() override;
};

#endif // !CUBEMESH_H