#include "inputManager.h"
#include <iostream>

InputManager* InputManager::m_Instance = NULL;	//sets instance to null

InputManager::InputManager() //defualt constructor
{
	SDL_Init(SDL_INIT_JOYSTICK);
	joy = SDL_JoystickOpen(0);
	cout << "controller name: " << SDL_JoystickName(joy);
}

InputManager::~InputManager()	//destructor
{

}

InputManager* InputManager::getInstance()
{
	//sets instance to new input manager object is the instance is null
	if (m_Instance == NULL)
	{
		m_Instance = new InputManager();
	}

	return m_Instance;	//returns instance
}


bool InputManager::isKeyDown(SDL_Scancode sdlcode)
{

	return states[sdlcode];	//returns the key state of the passed in sdl scancode
}

void InputManager::UpdateInput()
{
	states = SDL_GetKeyboardState(NULL);
	//gets the keyboard state
	
}

void InputManager::CheckEvents(Transform trans, Camera* camera)
{
	static SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		cout << "running" << endl;

		if (evt.type == SDL_JOYBUTTONDOWN)
		{
			cout << "hello joystick" << endl;

			//if (evt.jbutton.which == 1)
			{

				cout << "button press" << endl;
				//std::cout << evt.jaxis.value << "  stick value" << std::endl;

				/*
				if (evt.jaxis.value <= 0)
				{
				trans.GetPos().x += 50.0f;
				cout << "a move" << endl;
				}
				*/

			}	
			
		}

		if (evt.type == SDL_MOUSEMOTION)
		{
			mouseMoved = true;

		}
		else
		{

			mouseMoved = false;
		}
	}
}