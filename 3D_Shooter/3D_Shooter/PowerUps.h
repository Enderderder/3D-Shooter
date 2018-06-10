/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : PowerUps.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef POWERUPS_H
#define POWERUPS_H

// Inherited Include
#include "PhysicObject.h"

// Forward Declare
class CCamera;
class CCubeMap;

// Define Enum
enum EPOWERUPEFFECT
{
	HEAL,
	POWER,
	MOVESPD,
	ATKSPD
};

class CPowerUps : public CPhysicObject
{
public:
	CPowerUps() = default;
	CPowerUps(EPOWERUPEFFECT);
	~CPowerUps();

	void RenderObject(CCamera* _camera) override;
	void OnCollision(CGameObject* _other) override;

	EPOWERUPEFFECT GetEffect() const;

private:
	EPOWERUPEFFECT m_effect;

	CCubeMap* m_cubeMapTex;
};

#endif // !POWERUPS_H