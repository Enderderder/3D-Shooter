//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Player.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef PLAYER_H
#define PLAYER_H

// Inherited Include
#include "PhysicObject.h"
#include "CSound.h"

class CPlayer : public CPhysicObject
{
public:
	CPlayer() = default;
	CPlayer(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	CPlayer(CModel* _model, GLuint _programID);
	~CPlayer();

	void UpdateGameObeject() override;
	void OnCollision(CGameObject* _other) override;

	void ProcessMovement();
	void ProcessShooting();
	void ProcessBoundary();

private:

	// Private Member Function=================================================
	
	bool CheckBoarderUp(float _posZ);
	bool CheckBoarderDown(float _posZ);
	bool CheckBoarderLeft(float _posX);
	bool CheckBoarderRight(float _posX);

	// ========================================================================

	// Private Member Variable=================================================
	
	CSound m_pSound;

	int m_health;
	float m_movementSpd;
	float m_attackSpd;
	bool m_AbleToShoot;

	float BorderUp = -17.0f;
	float BorderDown = 17.0f;
	float BorderLeft = -19.0f;
	float BorderRight = 19.0f;

	bool m_IsLocalControl;

	// ========================================================================
};

#endif // !PLAYER_H