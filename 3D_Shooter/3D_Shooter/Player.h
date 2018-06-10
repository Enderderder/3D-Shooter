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

	bool MovementIsLegalVertical(glm::vec3 _Pos);
	bool MovementIsLegalHorizontal(glm::vec3 _Pos);
	void ProcessMovement();
	void ProcessShooting();

private:

	CSound m_pSound;

	int m_health;
	float m_movementSpd;
	float m_attackSpd;
	bool m_AbleToShoot;

	int BorderLeft = -19.f;
	int BorderRight = 19.f;
	int BorderDown = 17.f;
	int BorderUp = -17.f;

	bool m_IsLocalControl;
};

#endif // !PLAYER_H