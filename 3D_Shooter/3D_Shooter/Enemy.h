/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Enemy.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef ENEMY_H
#define ENEMY_H

// Inherited Include
#include "PhysicObject.h"

class CEnemy : public CPhysicObject
{
public:
	CEnemy() = default;
	CEnemy(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	~CEnemy();

	void UpdateGameObeject() override;
	void OnCollision(CGameObject* _other) override;

	void ProcessAI();

private:

	int m_health;
	int m_damage;
	float m_movementSpd;
};

#endif // !ENEMY_H