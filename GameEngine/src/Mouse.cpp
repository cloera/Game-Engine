#include <sb7.h>
#include "Game.h"
#include "Mouse.h"


// Get rid of later
extern Game *pGame;

Mouse::Mouse()
{
}

bool Mouse::GetKeyState(Mouse::BUTTONS button)
{
	// If mouse button was pressed
	if (pGame->GetMouseButton(button) == GLFW_PRESS)
	{
		return true;
	}
	// Mouse button was not pressed
	return false;
}

void Mouse::GetCursor(float & xPos, float & yPos)
{
	// Get position of mouse
	pGame->GetMousePosition(xPos, yPos);
}
