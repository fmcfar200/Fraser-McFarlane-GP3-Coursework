#pragma once

#include "Constants.h"
#include "Transform.h"
class InputManager
{
private:

	static InputManager* m_Instance;// instance
	const Uint8* states; //states

public:
	//construct + destruct
	InputManager();
	~InputManager();

	static InputManager* getInstance();	//getter for instance of input manager

	void UpdateInput(Transform trans);	//updates key inputs
	bool isKeyDown(SDL_Scancode sdlcode);	//checks is key is down
	SDL_Joystick *joy;


};