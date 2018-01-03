#pragma once

#include "Constants.h"

class Transform
{
public:
	//constructor
	Transform(const vec3& pos = vec3(), const vec3 rot = vec3(), const vec3& scale = vec3(1.0f, 1.0f, 1.0f)) :
		m_position(pos),
		m_rotation(rot),
		m_scale(scale){}

	//Creates Model Matrix
	inline mat4 GetModel() const
	{
		mat4 m_positionMat = translate(m_position); //translates pos
		//rotation matrix for x,y and z are created using glm rotate function
		mat4 m_rotXMat = rotate(m_rotation.x, vec3(1, 0, 0));	
		mat4 m_rotYMat = rotate(m_rotation.y, vec3(0, 1, 0));
		mat4 m_roatZMat = rotate(m_rotation.z, vec3(0, 0, 1));

		//scale matrix 
		mat4 m_scaleMat = scale(m_scale);

		//final rotation matrix
		mat4 m_rotMat = m_roatZMat * m_rotYMat * m_rotXMat;

		return m_positionMat * m_rotMat * m_scaleMat;	//returns Model Matrix
	}

	//Getters
	inline vec3& GetPos() 
	{ 
		return m_position;
	}
	inline vec3& GetRot() 
	{ 
		return m_rotation;
	}
	inline vec3& GetScale() 
	{ 
		return m_scale; 
	}

	//Setters
	inline void SetPos(const vec3& pos) 
	{ 
		m_position = pos; 
	}
	inline void SetRot(const vec3& rot) 
	{ 
		m_rotation = rot; 
	}
	inline void SetScale(const vec3& scale) 
	{ 
		m_scale = scale; 
	}
	
private:
	//member pos , rot and scale vectors
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_scale;
	
};