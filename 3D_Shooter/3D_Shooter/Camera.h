#pragma once
#include "Utility.h"
class Camera
{
public:
	Camera();
	~Camera();  


	Camera(glm::vec3 _Positition, glm::vec3 _Facing, glm::vec3 _Normal);
	void Update();

	glm::mat4 GetViewMatrix();
	void SetViewMatrix();
	void SetViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);

	glm::mat4 GetProjectionMatrix();
	void SetProjectionMatrix();

	glm::vec3 GetCameraPosition();
	void SetCameraPosition(glm::vec3 _Position);

	glm::vec3 GetCameraFacing();
	void SetCameraFacing(glm::vec3 _Facing);

	glm::vec3 GetCameraNormal();
	void SetCameraNormal(glm::vec3 _Normal);


	

private:
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFacing = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	
};

