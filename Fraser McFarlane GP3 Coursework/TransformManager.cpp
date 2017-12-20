#include "TransformManager.h"


TransformManager::TransformManager(const vec3& position, const vec3& rot, const vec3& scale)
{
	this->thePosition = position;
	this->theRotation = rot;
	this->theScale = scale;
}


TransformManager::~TransformManager()
{
}


inline mat4 TransformManager::CalcModelMat() const
{

}
inline vec3* TransformManager::GetPosition()
{
	return &thePosition;
}
inline vec3* TransformManager::GetRotation()
{
	return &theRotation;
}
inline vec3* TransformManager::GetScale()
{
	return &theScale;
}

inline void TransformManager::SetPosition(vec3& pos)
{
	this->thePosition = pos;
}
inline void TransformManager::SetRotation(vec3& rot)
{
	this->theRotation = rot;
}
inline void TransformManager::SetScale(vec3& scale)
{
	this->theScale = scale;
}
