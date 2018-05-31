//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : Camera.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

// This Include
#include "Camera.h"


Camera::Camera()
CCamera::CCamera()
{
	m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	m_CameraFacing = glm::vec3(0.0f, 0.0f, -1.0f);
	m_CameraNormal = glm::vec3(0.0f, 1.0f, 0.0f);

	CalcViewMatrix();
	SetProjectionMatrix();
}

CCamera::CCamera(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal)
{
	SetCameraPosition(_Position);
	SetCameraFacing(_Facing);
	SetCameraNormal(_Normal);

	SetViewMatrix();

	CalcViewMatrix();
	SetProjectionMatrix();
}


Camera::~Camera()
CCamera::~CCamera()
{
}

void Camera::Update()
void CCamera::Update()
{
	

}

glm::mat4 Camera::GetViewMatrix()
glm::mat4 CCamera::GetViewMatrix() const
{
	return(m_ViewMatrix);
}
//Defualt
void Camera::SetViewMatrix()

void CCamera::CalcViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFacing, m_CameraNormal);
	m_ViewMatrix = glm::lookAt(
		m_CameraPosition, 
		m_CameraPosition + m_CameraFacing, 
		m_CameraNormal);
}
void Camera::SetViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal)
void CCamera::CalcViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal)
{
	m_ViewMatrix = glm::lookAt(_Position, _Position + _Facing, _Normal);
	m_ViewMatrix = glm::lookAt(
		_Position, 
		_Position + _Facing, 
		_Normal);
}

glm::mat4 Camera::GetProjectionMatrix()
glm::mat4 CCamera::GetProjectionMatrix() const
{
	return(m_ProjectionMatrix);
}
void Camera::SetProjectionMatrix()
void CCamera::SetProjectionMatrix()
{
	m_ProjectionMatrix = glm::ortho((float) -util::SCR_WIDTH / 2.0f, (float)util::SCR_WIDTH / 2.0f,(float) -util::SCR_HEIGHT/ 2.0f, (float)util::SCR_HEIGHT / 2.0f, 0.1f, 100.0f);
	//m_ProjectionMatrix = glm::ortho((float)-util::SCR_WIDTH / 2.0f, (float)util::SCR_WIDTH / 2.0f, (float)-util::SCR_HEIGHT / 2.0f, (float)util::SCR_HEIGHT / 2.0f, 0.1f, 100.0f);
	m_ProjectionMatrix = glm::perspective(45.0f, 
		(float)util::SCR_WIDTH / (float)util::SCR_HEIGHT, 0.1f, 3000.0f);
}

glm::vec3 Camera::GetCameraPosition()
glm::vec3 CCamera::GetCameraPosition() const
{
	return(m_CameraPosition);
}
void Camera::SetCameraPosition(glm::vec3 _Position)
void CCamera::SetCameraPosition(glm::vec3 _Position)

{
	m_CameraPosition = _Position;
}

glm::vec3 Camera::GetCameraFacing()
glm::vec3 CCamera::GetCameraFacing() const
{
	return(m_CameraFacing);
}
void Camera::SetCameraFacing(glm::vec3 _Facing)
void CCamera::SetCameraFacing(glm::vec3 _Facing)
{
	m_CameraFacing = _Facing;
}

glm::vec3 Camera::GetCameraNormal()
glm::vec3 CCamera::GetCameraNormal() const
{
	return(m_CameraNormal);
}
void Camera::SetCameraNormal(glm::vec3 _Normal)
void CCamera::SetCameraNormal(glm::vec3 _Normal)
{
	m_CameraNormal = _Normal;
}

}