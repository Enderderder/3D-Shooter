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

class CPlayer : public CPhysicObject
{
public:
	CPlayer() = default;
	CPlayer(CMesh* _mesh, GLuint _textureID, GLuint _programID);
	CPlayer(CModel* _model, GLuint _programID);

	glm::vec3 GetPosistion(CPlayer* _Player);


	~CPlayer();

	void UpdateGameObeject() override;

	void ProcessMovement();
	void ProcessShooting();

private:

	int m_health;
	float m_movementSpd;
	float m_attackSpd;

	bool m_IsLocalControl;
};

#endif // !PLAYER_H