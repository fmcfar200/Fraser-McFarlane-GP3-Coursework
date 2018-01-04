#include "SDLDisplay.h"
#include <GL\glew.h>
#include <iostream>


SDLDisplay::SDLDisplay(int windowWidth, int windowHeight, const std::string& windowName)
{
	//Initialises everything for SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Sets attributes to help with displaying colours etc
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Creates the window and context and binds the information to the relevant variable
	m_theWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	m_theGLContext = SDL_GL_CreateContext(m_theWindow);

	//Initialises glew and an error check is performed
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialise" << std::endl;
	}

	//Sets closed to false
	m_displayClosed = false;

	//Enables a depth test and face culling to help with drawing objects within the window
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

SDLDisplay::~SDLDisplay()
{
	//Clears any information that was created within the constructor
	SDL_GL_DeleteContext(m_theGLContext);
	SDL_DestroyWindow(m_theWindow);
	SDL_Quit();
}

void SDLDisplay::ClearDisplayColour(float r, float g, float b, float a)
{
	//Clears the display screen
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool SDLDisplay::IsClosed()
{
	//Used to check the status of m_isClosed
	return m_displayClosed;
}

void SDLDisplay::setOrthographicProj(int width, int height)
{
	/*
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, 0.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
}

void SDLDisplay::setMVP(int width, int height)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);
	Resize(width, height);

}

void SDLDisplay::Resize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(45.0f, float(width) / float(height), 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void SDLDisplay::SwapBuffers()
{
	//Swaps the buffers and checks if the window has been closed
	SDL_GL_SwapWindow(m_theWindow);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_displayClosed = true;
		}
	}
}