#pragma once

#include "Constants.h"

using namespace glm;
class Camera
{

private:
	mat4 m_perspectiveMat;	//perspective matrix
	vec3 m_position;	//position
	vec3 m_forwardVec; //forward vector
	vec3 m_upVec;	//up vector

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

	//Calculates the view projection matrix
	inline mat4 GetViewProjectionMatrix() const
	{
		return m_perspectiveMat * lookAt(m_position, m_position + m_forwardVec, m_upVec);

	}



};