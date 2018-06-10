//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : CAIMgr.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//
#ifndef AIMgr_H
#define AIMgr_H

#include "CAIMgr.h"


CAIMgr::CAIMgr(CMesh* _mesh, GLuint _textureID, GLuint _programID, AIType _AIType, CGameObject* _Target) :


	m_movementSpd(0.01f)

{
	m_ColliderRad = 1.0f;
	AI = _AIType;
	m_pTarget = _Target;
	InitializeObject(_mesh, _textureID, _programID);
}

CAIMgr::CAIMgr(CModel* _model, GLuint _programID, AIType _AIType, CGameObject* _Target) :


	m_movementSpd(0.01f)

{
	AI = _AIType;
	m_pTarget = _Target;
	InitializeObject(_model, _programID);
}

void CAIMgr::UpdateGameObeject()
{
	glm::vec3 resultMovement(0.0f, 0.0f, 0.0f);

	switch (AI)
	{
	case SEEK:
	{
		resultMovement = m_pSeek.UpdateGameObject(m_pTarget, m_movementSpd, this->m_Position);
	}
		break;

	case FLEE:
	{
		resultMovement = m_pFlee.UpdateGameObject(m_pTarget, m_movementSpd, this->m_Position);
	}
		break;

	case WANDER:
	{
		resultMovement = m_pWander.UpdateGameObject(m_pTarget, m_movementSpd, this->m_Position);
	}
		break;

	case CONTAINMENT:
	{

	}
		break;

	default:
	{
	
	}
		break;
	}


	float fMag = sqrtf(powf(resultMovement.x, 2) + powf(resultMovement.z, 2));
	if (fMag != 0.0f)
	{
		glm::vec3 uniVec = resultMovement / fMag;
		resultMovement = uniVec * m_movementSpd;
		this->AddPosition(resultMovement);
	}


}

CAIMgr::~CAIMgr()
{

}


#endif // !AIMgr_H
