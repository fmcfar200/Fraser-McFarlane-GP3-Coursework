#include "inputManager.h"
#include <iostream>

InputManager* InputManager::m_Instance = NULL;	//sets instance to null

InputManager::InputManager() //defualt constructor
{

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


bool InputManager::isKeyDown(SDL_Scancode scanCode)
{

	return m_KeyboardStates[scanCode];	//returns the key state of the passed in sdl scancode
}

void InputManager::UpdateInput()
{
	m_KeyboardStates = SDL_GetKeyboardState(NULL);	//gets the keyboard state

}