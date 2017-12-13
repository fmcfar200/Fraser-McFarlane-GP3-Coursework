/*
==========================================================================
Shapes.h
==========================================================================
*/

#ifndef _SHAPES_H
#define _SHAPES_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "Colours.h"
#include "Texture.h"

class Shapes : public windowOGL
{
public:
	Shapes();
	virtual void render(float rotAngle) = 0;
	float getRotAngle();
	void setRotAngle(float rotAngle);
	void prepare(float rAngle);
	virtual void initialise(Texture theTexture) = 0;

	PFNGLGENBUFFERSARBPROC glGenBuffers = NULL;
	PFNGLBINDBUFFERPROC glBindBuffer = NULL;
	PFNGLBUFFERDATAPROC glBufferData = NULL;

private:
	float m_rotAngle;
};

#endif