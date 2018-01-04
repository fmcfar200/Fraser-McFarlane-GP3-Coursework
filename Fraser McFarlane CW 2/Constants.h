#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define WIDTH 1400
#define HEIGHT 1000
#define MODEL_PATH "res/models/"
#define AUDIO_PATH "res/audio/"
#define TEXTURE_PATH "res/textures/"
#define SHADER_PATH "res/shaders"

//SDL 
#include <SDL2\SDL.h>

//OpenGL and Windows
#include <GL\glew.h>
#include <Windows.h>

//GLM Maths Library
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm\gtc\matrix_transform.hpp"

//OpenAL for sounds
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <OpenAL\alut.h>

//Utilities
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cassert>


//Commonly used namepaces
using namespace std;
using namespace glm;

struct lightColour4 // light struct
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha

};

struct colour3f //colour struct
{
	colour3f(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
};

#endif // !_CONSTANTS_H


