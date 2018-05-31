#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : Camera.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef CAMERA_H
#define CAMERA_H

// Local Include
#include "Utility.h"
class Camera

class CCamera
{
public:
	Camera();
	~Camera();  

	CCamera();
	~CCamera();

	Camera(glm::vec3 _Positition, glm::vec3 _Facing, glm::vec3 _Normal);
	CCamera(glm::vec3 _Positition, glm::vec3 _Facing, glm::vec3 _Normal);
	void Update();

	glm::mat4 GetViewMatrix();
	void SetViewMatrix();
	void SetViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);
	glm::mat4 GetViewMatrix() const;
	void CalcViewMatrix();
	void CalcViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetProjectionMatrix() const;
	void SetProjectionMatrix();

	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraPosition() const;
	void SetCameraPosition(glm::vec3 _Position);

	glm::vec3 GetCameraFacing();
	glm::vec3 GetCameraFacing() const;
	void SetCameraFacing(glm::vec3 _Facing);

	glm::vec3 GetCameraNormal();
	glm::vec3 GetCameraNormal() const;
	void SetCameraNormal(glm::vec3 _Normal);


	

private:
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFacing = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraFacing;
	glm::vec3 m_CameraNormal;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	
};

#endif // !CAMERA_H