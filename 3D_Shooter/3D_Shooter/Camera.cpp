#include "Camera.h"


Camera::Camera()
{

	SetViewMatrix();

	SetProjectionMatrix();
}

Camera::Camera(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal)
{
	SetCameraPosition(_Position);
	SetCameraFacing(_Facing);
	SetCameraNormal(_Normal);

	SetViewMatrix();

	SetProjectionMatrix();
}


Camera::~Camera()
{
}

void Camera::Update()
{
	
}

glm::mat4 Camera::GetViewMatrix()
{
	return(m_ViewMatrix);
}
//Defualt
void Camera::SetViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFacing, m_CameraNormal);
}
void Camera::SetViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal)
{
	m_ViewMatrix = glm::lookAt(_Position, _Position + _Facing, _Normal);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return(m_ProjectionMatrix);
}
void Camera::SetProjectionMatrix()
{
	m_ProjectionMatrix = glm::ortho((float) -util::SCR_WIDTH / 2.0f, (float)util::SCR_WIDTH / 2.0f,(float) -util::SCR_HEIGHT/ 2.0f, (float)util::SCR_HEIGHT / 2.0f, 0.1f, 100.0f);
}

glm::vec3 Camera::GetCameraPosition()
{
	return(m_CameraPosition);
}
void Camera::SetCameraPosition(glm::vec3 _Position)
{
	m_CameraPosition = _Position;
}

glm::vec3 Camera::GetCameraFacing()
{
	return(m_CameraFacing);
}
void Camera::SetCameraFacing(glm::vec3 _Facing)
{
	m_CameraFacing = _Facing;
}

glm::vec3 Camera::GetCameraNormal()
{
	return(m_CameraNormal);
}
void Camera::SetCameraNormal(glm::vec3 _Normal)
{
	m_CameraNormal = _Normal;
}

