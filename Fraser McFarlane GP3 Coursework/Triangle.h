/*
==========================================================================
Triangle.h
==========================================================================
*/

#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "windowOGL.h"

class Triangle : public windowOGL
{
public:
	Triangle();
	void renderTri(float rotAngle);
	float getRotAngle();
	void setRotAngle(float rotAngle);
	void prepareTri(float dt);

private:
	float m_rotAngle;
};

#endif