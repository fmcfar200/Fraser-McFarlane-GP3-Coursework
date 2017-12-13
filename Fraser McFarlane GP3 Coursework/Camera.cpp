/*
==========================================================================
Camera.h
==========================================================================
*/

#include "Camera.h"

Camera::Camera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}


Camera::Camera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

Camera::~Camera()
{
	
}

void Camera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

const glm::vec4 Camera::getTheViewPort()
{
	return m_viewPort;
}

void Camera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void Camera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

glm::vec3 Camera::getTheCameraPos()
{
	return m_cameraPos;
}

void Camera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 Camera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

void Camera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 Camera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

void Camera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 Camera::getTheCameraDirection()
{
	return m_cameraDirection;
}

void Camera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 Camera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

void Camera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width/height;
}

GLfloat Camera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

glm::mat4 Camera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 Camera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

void Camera::setCamViewMatrix()
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraLookAt, m_cameraUpVector);
}

glm::mat4 Camera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

void Camera::update()
{
	setTheCameraDirection();
	setTheCameraStrafe();
	setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 300.0f);
	setCamViewMatrix();
}
