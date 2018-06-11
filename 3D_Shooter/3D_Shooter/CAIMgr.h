//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CSIMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef AIMGR_H
#define AIMGR_H

enum AIType
{
	SEEK,
	FLEE,
	PURSUE,
	WANDER,
	CONTAINMENT

};

// Inherited Include
#include "PhysicObject.h"

class CAIMgr : public CPhysicObject
{
public:
	CAIMgr(CMesh* _mesh, GLuint _textureID, GLuint _programID, AIType _AIType, CGameObject* _Target);
	~CAIMgr();

	void UpdateGameObeject() override;
	void OnCollision(CGameObject* _other) override;

private:

	// MemberFunction
	void AiSeek(glm::vec3 _TargetPoint);
	void AiFlee(glm::vec3 _TargetPoint);
	void AiPursue(CGameObject* _Target);
	void AiArrival(CGameObject* _Target);
	void AiWander();
	void AiWallBounce();

	bool IsNotPanicArea(glm::vec3 _PlayerPos);
	void SetAngle(glm::vec3& _vector, float _angle);

	// Member Variable
	float m_WanderAngle;

	float m_movementSpd;

	AIType AI;
	CGameObject* m_pTarget;
};

#endif // !AIMGR_H