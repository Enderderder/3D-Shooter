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
	WANDER,
	CONTAINMENT,
	ARRIVE

};

// Inherited Include
#include "Player.h"
#include "CSeek.h"
#include "CFlee.h"
#include "CWander.h"
#include "CContainment.h"

class CAIMgr : public CPhysicObject
{
public:
	CAIMgr(CMesh* _mesh, GLuint _textureID, GLuint _programID, AIType _AIType, CGameObject* _Target);
	//CAIMgr(CModel* _model, GLuint _programID, AIType _AIType, CGameObject* _Target);
	~CAIMgr();

	void UpdateGameObeject() override;
	void OnCollision(CGameObject* _other) override;

private:

	// MemberFunction
	void AiSeek(CGameObject* _Target);
	void AiFlee(CGameObject* _Target);
	void AiArrival(CGameObject* _Target);
	void AiWander();

	bool IsNotPanicArea(glm::vec3 _PlayerPos);
	void SetAngle(glm::vec3& _vector, float _angle);

	float m_WanderAngle;

	float m_movementSpd;

	CSeek m_pSeek;
	CFlee m_pFlee;
	CWander m_pWander;
	AIType AI;
	CGameObject* m_pTarget;
};



#endif // !AIMGR_H