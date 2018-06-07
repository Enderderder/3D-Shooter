//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Bullet.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef BULLET_H
#define BULLET_H

// Inherited Include
#include "PhysicObject.h"

class CBullet : public CPhysicObject
{
public:
	CBullet() = default;
	CBullet(glm::vec3 _dirVec);
	~CBullet();

private:

	float m_damage;
	float m_bulletSpeed;
};

#endif // !BULLET_H