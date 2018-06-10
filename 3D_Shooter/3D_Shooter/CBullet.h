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
	CBullet(glm::vec3 _dirVec, float _damage);
	~CBullet();

	void UpdateGameObeject() override;
	void OnCollision(CGameObject* _other) override;

	float GetDamage() const;

private:

	float m_damage;
	float m_bulletSpeed;
	int m_counter;
};

#endif // !BULLET_H