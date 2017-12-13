#include "Model.h"

Model::Model()
{
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = 0.0f;
	m_mdlDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlSpeed = 0.0f;
	m_IsActive = false;
	m_mdlScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	m_TextureID = 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Setters
// +++++++++++++++++++++++++++++++++++++++++++++

void Model::setPosition(glm::vec3 mdlPosition)
{
	m_mdlPosition = mdlPosition;
}

void Model::setRotation(GLfloat mdlRotation)
{
	m_mdlRotation = mdlRotation;
}

void Model::setDirection(glm::vec3 mdlDirection)
{
	m_mdlDirection = mdlDirection;
}

void Model::setSpeed(float mdlSpeed)
{
	m_mdlSpeed = mdlSpeed;
}

void Model::setIsActive(bool mdlIsActive)
{
	m_IsActive = mdlIsActive;
}

void Model::setMdlDimensions(mdlDimensions mdlDims)
{
	m_Dimensions = mdlDims;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

void Model::setMdlRadius(float mdlRadius)
{
	m_mdlRadius = mdlRadius;
}

void Model::setScale(glm::vec3 mdlScale)
{
	m_mdlScale = mdlScale;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Getters
// +++++++++++++++++++++++++++++++++++++++++++++

glm::vec3 Model::getPosition()
{
	return m_mdlPosition;
}

GLfloat Model::getRotation()
{
	return m_mdlRotation;
}

glm::vec3 Model::getDirection()
{
	return m_mdlDirection;
}

float Model::getSpeed()
{
	return m_mdlSpeed;
}

bool Model::isActive()
{
	return m_IsActive;
}

mdlDimensions Model::getMdlDimensions()
{
	return m_Dimensions;
}

float Model::getMdlRadius()
{
	return m_mdlRadius;
}

glm::vec3 Model::getScale()
{
	return m_mdlScale;
}

void Model::setTextureID(GLuint theTextureID)
{
	m_TextureID = theTextureID;
}

void Model::initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive)
{
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setScale(mdlScale);
	setDirection(mdlDirection);
	setSpeed(mdlSpeed);
	setIsActive(mdlIsActive);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(mdlPos.x,mdlPos.y,mdlPos.z);
}

bool Model::SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius)
{
	const float distSq = lengthSQRD(m_mdlPosition - mdlPosition);

	const float sumRadius = (m_mdlRadius + mdlRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float Model::lengthSQRD(glm::vec3 mdlLength)
{
	return (mdlLength.x * mdlLength.x) + (mdlLength.y * mdlLength.y) + (mdlLength.z * mdlLength.z);
}

/*
=================================================================
Attach the input manager to the sprite
=================================================================
*/
void Model::attachInputMgr(InputManager* inputMgr)
{
	m_InputMgr = inputMgr;
}
/*
=================================================================
Attach the sound manager to the sprite
=================================================================
*/
void Model::attachSoundMgr(SoundManager* soundMgr)
{
	m_SoundMgr = soundMgr;
}

Model::~Model()
{

}
