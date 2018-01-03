#pragma once

#include "Constants.h"
class InputManager
{
private:

	static InputManager* m_Instance;// instance
	const Uint8* m_KeyboardStates; //states

public:
	//construct + destruct
	InputManager();
	~InputManager();

	static InputManager* getInstance();	//getter for instance of input manager

	void UpdateInput();	//updates key inputs
	bool isKeyDown(SDL_Scancode scanCode);	//checks is key is down
	//static void ReleaseInput();	//releases input and deletes instance

};