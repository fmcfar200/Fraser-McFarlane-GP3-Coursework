#pragma once

#include "Constants.h"
#include "Transform.h"
#include "Camera.h"
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

	void UpdateInput();	//updates key inputs
	void CheckEvents(Transform trans, Camera* camera);
	bool isKeyDown(SDL_Scancode sdlcode);	//checks is key is down
	SDL_Joystick *joy;

	bool mouseMoved = false;

	bool leftMove, rightmove, upmove, downmove = false;

	bool start, fire, camswitch, mute = false;
};