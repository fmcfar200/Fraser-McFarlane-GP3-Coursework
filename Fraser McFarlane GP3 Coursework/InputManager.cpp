/*
== == == == == == == == =
InputManager.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/

#include "InputManager.h"

InputManager* InputManager::pInstance=NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
InputManager* InputManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new InputManager();
	}
	return InputManager::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
InputManager::InputManager()
{
	for (int key = 0; key < 256; key++)		// clear key down buffer
	{
		keysDownBuffer[key] = false;
	}
	for (int key = 0; key < 256; key++)			// clear key pressed array
	{
		keysPressedBuffer[key] = false;
	}
	
	mousePos.x = 0;                         // screen X
	mousePos.y = 0;                         // screen Y
	leftMouseBtn = false;               // true if left mouse button is down
	middleMouseBtn = false;               // true if middle mouse button is down
	rightMouseBtn = false;               // true if right mouse button is down

}

/*
=============================================================================
   Set true in the keysDown and keysPessed array for this key
=============================================================================
*/
void InputManager::keyDown(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = true;    // update keysDown array
		keysPressedBuffer[wParam] = true; // update keysPressed array
	}
}

/*
=============================================================================
   Set false in the keysDown array for this key
=============================================================================
*/
void InputManager::keyUp(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = false;
	}
}
/*
=============================================================================
   Returns true if the specified VIRTUAL KEY is down, otherwise false.
=============================================================================
*/
bool InputManager::isKeyDown(int vkey)
{
	if (vkey < 256)
	{
		return keysDownBuffer[vkey];
	}
	else
	{
		return false;
	}
}
/*
=============================================================================
   Return true if the specified VIRTUAL KEY has been pressed
=============================================================================
*/
bool InputManager::wasKeyPressed(int vkey)
{
	if (vkey < 256)
	{
		return keysPressedBuffer[vkey];
	}		
	else
	{
		return false;
	}	
}
/*
=============================================================================
   Return true if any key was pressed
=============================================================================
*/
bool InputManager::anyKeyPressed()
{
	for (BYTE keys = 0; keys < 256; keys++)
	{
		if (keysPressedBuffer[keys] == true)
		{
			return true;
		}
	}
	return false;
}
/*
=============================================================================
   Clear the specified key press
=============================================================================
*/
void InputManager::clearKeyPress(int vkey)
{
	if (vkey < 256)
	{
		keysPressedBuffer[vkey] = false;
	}
}
/*
=============================================================================
   Clear buffers, single or combined
=============================================================================
*/
void InputManager::clearBuffers(BYTE bufferToClear)
{
	if (bufferToClear & KEYS_DOWN_BUFFER)       // if clear keys down
	{
		for (int key = 0; key < 256; key++)
		{
			keysDownBuffer[key] = false;
		}
	}
	if (bufferToClear & KEYS_PRESSED_BUFFER)    // if clear keys pressed
	{
		for (int key = 0; key < 256; key++)
		{
			keysPressedBuffer[key] = false;
		}
	}
	if (bufferToClear & MOUSE_BUFFER)           // if clear mouse
	{
		mousePos.x = 0;
		mousePos.y = 0;
	}
}
/*
=============================================================================
    Reads mouse screen position into mouseX, mouseY
=============================================================================
*/
void InputManager::mouseXY(LPARAM lParam)
{
	mousePos.x = LOWORD(lParam);
	mousePos.y = HIWORD(lParam);
}

/*
=============================================================================
   Save state of mouse button
=============================================================================
*/
void InputManager::setLeftMouseBtn(bool b)
{
	leftMouseBtn = b;
}
/*
=============================================================================
   Save state of mouse button
=============================================================================
*/
void InputManager::setMiddleMouseBtn(bool b)
{
	middleMouseBtn = b;
}
/*
=============================================================================
   Save state of mouse button
=============================================================================
*/
void InputManager::setRightMouseBtn(bool b)
{
	rightMouseBtn = b;
}
/*
=============================================================================
   Return mouse X position
=============================================================================
*/
int  InputManager::getMouseXPos()
{
	return mousePos.x;
}
/*
=============================================================================
   Return mouse Y position
=============================================================================
*/
int  InputManager::getMouseYPos()
{
	return mousePos.y;
}
/*
=============================================================================
   Return state of left mouse button.
=============================================================================
*/
bool InputManager::getLeftMouseBtn()
{
	return leftMouseBtn;
}
/*
=============================================================================
   Return state of middle mouse button.
=============================================================================
*/
bool InputManager::getMiddleMouseBtn()
{
	return middleMouseBtn;
}
/*
=============================================================================
   Return state of right mouse button.
=============================================================================
*/
bool InputManager::getRightMouseBtn()
{
	return rightMouseBtn;
}

