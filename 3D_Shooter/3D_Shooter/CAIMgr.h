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
	CONTAINMENT,
	ARRIVE,
	FLOCK
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
	glm::vec3 AiSeek(glm::vec3 _TargetPoint);
	glm::vec3 AiFlee(glm::vec3 _TargetPoint);
	glm::vec3 AiPursue(CGameObject* _Target);
	glm::vec3 AiArrival(CGameObject* _Target);
	glm::vec3 AiWander();
	glm::vec3 AiWallBounce();
	glm::vec3 Separate(std::vector<CGameObject*> _objVec);

	bool IsNotPanicArea(glm::vec3 _PlayerPos);
	void SetAngle(glm::vec3& _vector, float _angle);

	// Member Variable
	float m_WanderAngle;

	float m_movementSpd;

	AIType AI;
	CGameObject* m_pTarget;
};

#endif // !AIMGR_H