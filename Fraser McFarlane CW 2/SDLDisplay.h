#pragma once

#include "Constants.h"
class SDLDisplay
{
private:
	SDL_Window* m_theWindow;	//the window
	SDL_GLContext m_theGLContext;	//the opengl context
	bool m_displayClosed;	//boolean for checking close


public:
	SDLDisplay()	//default constructor
	{

	}

	SDLDisplay(int windowWidth, int windowHeight, const std::string& windowName);	 //constructor that takes in dimesions and name for the window
	~SDLDisplay();	//destructor

	void ClearDisplayColour(float r, float g, float b, float a);	//sets the clear colour of the display
	void SwapBuffers();	//swaps buffer for a window 
	bool IsClosed();	//checks if the window is closed

	void setOrthographicProj(int width, int height);	//sets orthographic projection
	void Resize(int width, int height);	//resize
	void setMVP(int width, int height);	//sets back to model view




};