#pragma once

#include "Constants.h"

class Camera
{

private:
	mat4 m_perspectiveMat;	//perspective matrix
	vec3 m_position;	//position
	vec3 m_forwardVec; //forward vector
	vec3 m_upVec;	//up vector

	uint32 thisFrame;
	GLfloat delta;
	GLfloat previousFrame = 0.0f;
	float speed = 1.0f;

	float prevX,
		prevY = 0.0f;

	int mouseX,
		mouseY = 0;

	float yaw, pitch = 0.0f;


public:
	Camera()
	{

	}// default constructor

	//Creates the camera
	Camera(const vec3& pos, float fov, float aspect, float cNear, float cFar)
	{
		//Sets the persective 
		m_perspectiveMat = perspective(fov, aspect, cNear, cFar);
		//Sets the position
		m_position = pos;
		//Sets the forward vector
		m_forwardVec = vec3(0, 0, 1);
		//sets the up vector
		m_upVec = vec3(0, 1, 0);

		setView();
	}
		
	//getters
	vec3 GetForwardV() const
	{
		return m_forwardVec;
	}

	vec3 GetUpV() const
	{
		return m_upVec;
	}

	inline mat4 GetView()
	{
		viewmat = lookAt(m_position, m_position + m_forwardVec, m_upVec);
		return viewmat;
	}
	//Calculates the view projection matrix
	inline mat4 GetViewProjectionMatrix() const
	{
		return m_perspectiveMat * lookAt(m_position, m_position + m_forwardVec, m_upVec);

	}

	void setView()
	{
		viewmat = lookAt(m_position, m_position + m_forwardVec, m_upVec);
	}

	void Rotation()
	{
		thisFrame = SDL_GetTicks();
		delta = thisFrame - previousFrame;
		previousFrame = thisFrame;

		speed = speed*delta;

		SDL_GetGlobalMouseState(&mouseX, &mouseY);

		GLfloat offsetX = mouseX - prevX;
		GLfloat offsetY = prevY - mouseY;
		prevY = mouseY;
		prevX = mouseX;

		GLfloat sensitivity = 0.1f;

		offsetX *= sensitivity;
		offsetY *= sensitivity;


		yaw += offsetX;
		pitch += offsetY;

		vec3 tempForward;
		tempForward.x = cos(radians(yaw)) * cos(radians(pitch));
		tempForward.y = sin(radians(pitch));
		tempForward.z = sin(radians(yaw)) * cos(radians(pitch));

		m_forwardVec = normalize(tempForward);



	}

	mat4 viewmat;
};