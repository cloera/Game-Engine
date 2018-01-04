#include <sb7.h>

#include "Game.h"
#include "Keyboard.h"

// Get rid of later
extern Game *pGame;

Keyboard::Keyboard()
{
}

bool Keyboard::GetKeyState(Keyboard::KEYS key)
{
	// If key was pressed
	if (pGame->GetKey(key) == GLFW_PRESS)
	{
		return true;
	}
	// Key was not pressed
	return false;
}
