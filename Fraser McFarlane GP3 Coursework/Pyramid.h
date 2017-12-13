/*
==========================================================================
cPyramid.h
==========================================================================
*/

#ifndef _PYRAMID_H
#define _PYRAMID_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "Colours.h"
#include "Shapes.h"

class Pyramid : public Shapes
{
public:
	Pyramid();
	virtual void render(float rotAngle);
	virtual void initialise(Texture theTexture);

private:

	glm::vec3 m_Top;
	glm::vec3 m_frontBottomLeft;
	glm::vec3 m_frontBottomRight;

	glm::vec3 m_rightBottomLeft;
	glm::vec3 m_rightBottomRight;

	glm::vec3 m_leftBottomLeft;
	glm::vec3 m_leftBottomRight;

	glm::vec3 m_backBottomLeft;
	glm::vec3 m_backBottomRight;

	glm::vec3 m_Faces[24];
	GLuint m_Indices[18];

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colourList;
	GLuint m_VertexBufferObjects[3];

};

#endif