/*
==================================================================================
Light.cpp
==================================================================================
*/

#ifndef _LIGHT_H
#define _LIGHT_H

#include "Constants.h"


class Light
{
public:
	Light();
	Light(GLenum lightID, lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, vec4 position, vec3 spotDirection
		, GLfloat  spotExponent, GLfloat  spotCutoff, GLfloat  constantAttenuation, GLfloat  linearAttenuation, GLfloat  quadraticAttenuation);

	void lightOn();
	void lightOff();

	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;

	vec4 m_Position;
	vec3 m_SpotDirection;

private:

	GLenum m_LightID;
	

	GLfloat  m_SpotExponent;
	GLfloat  m_SpotCutoff;
	GLfloat  m_ConstantAttenuation;
	GLfloat  m_LinearAttenuation;
	GLfloat  m_QuadraticAttenuation;
};

#endif