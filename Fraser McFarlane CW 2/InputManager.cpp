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
		if (evt.type == SDL_JOYBUTTONDOWN)
		{
			cout << (int)evt.jbutton.button << endl;
			if (evt.jbutton.button == 0)
			{
				fire = true;
			}
			else if (evt.jbutton.button == 7)
			{
				start = true;
			}
			else if (evt.jbutton.button == 6)
			{
				mute = true;
			}
			else if (evt.jbutton.button == 1)
			{
				camswitch = true;
			}

		}
		if (evt.type == SDL_JOYAXISMOTION)
		{

			if (evt.jaxis.value < -3200 || evt.jaxis.value > 3200)
			{

				if (evt.jaxis.axis == 0)
				{

					if (evt.jaxis.value < -3200)
					{
						leftMove = true;
						rightmove = false;
						upmove = false;
						downmove = false;
					}
					else if (evt.jaxis.value > 3200)
					{
						leftMove = false;
						rightmove = true;
						upmove = false;
						downmove = false;
					}
					else
					{
						leftMove = false;
						rightmove = false;
						upmove = false;
						downmove = false;
					}

				}

				if (evt.jaxis.axis == 1)
				{
					if (evt.jaxis.value < -3200)
					{
						leftMove = false;
						rightmove = false;
						upmove = false;
						downmove = true;
					}
					else if (evt.jaxis.value > 3200)
					{
						leftMove = false;
						rightmove = false;
						upmove = true;
						downmove = false;
					}
					else
					{
						leftMove = false;
						rightmove = false;
						upmove = false;
						downmove = false;
					}
				}
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