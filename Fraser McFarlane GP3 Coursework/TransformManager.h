#pragma once
#include "GameConstants.h"
using namespace glm;

class TransformManager
{

private:
	vec3 thePosition;
	vec3 theRotation;
	vec3 theScale;

public:
	TransformManager(const vec3& position,const vec3& rot,const vec3& scale = vec3(1.0f,1.0f,1.0f));
	~TransformManager();

	inline mat4 CalcModelMat() const;
	inline vec3* GetPosition();
	inline vec3* GetRotation();
	inline vec3* GetScale();

	inline void SetPosition(vec3& pos);
	inline void SetRotation(vec3& rot);
	inline void SetScale(vec3& scale);

	
};

