//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : GameObject.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Local Includes
#include "Mesh.h"
#include "Utility.h"

class CGameObject
{
public:
	CGameObject() = default;
	CGameObject();

	~CGameObject();

private:
	CMesh* m_ObjMesh;
	GLuint* m_textureID;
};

#endif // !GAMEOBJECT_Hs