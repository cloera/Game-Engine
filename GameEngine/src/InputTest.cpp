#pragma warning( push )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4571 )
#pragma warning( disable : 4625 )
#pragma warning( disable : 4626 )
#pragma warning( disable : 5026 )
#pragma warning( disable : 5027 )
#pragma warning( disable : 4774 )
#include <string>
#pragma warning( pop )

#include "Trace.h"
#include "InputTest.h"
#include "InputManager.h"
#include "Keyboard.h"


void KeyboardTest()
{
	Keyboard *key = InputManager::GetKeyboard();

	// Quick and dirty test, if these work the rest do.
	// ---> try a,s,d,<SPACE> keys
	std::string a;
	std::string b;
	std::string c;
	std::string d;

	if (key->GetKeyState(Keyboard::KEYS::KEY_A))
	{
		a = " A";
	}

	if (key->GetKeyState(Keyboard::KEYS::KEY_S))
	{
		b = " S";
	}

	if (key->GetKeyState(Keyboard::KEYS::KEY_D))
	{
		c = " D";
	}

	if (key->GetKeyState(Keyboard::KEYS::KEY_SPACE))
	{
		d = " <SPACE>";
	}

	std::string total = a + b + c + d;
	Trace::out("Key:%s \n", total.c_str());
}


void MouseTest()
{
	Mouse *mouse = InputManager::GetMouse();

	// Quick and dirty test, if these work the rest do.
	// --> try move the mouse inside the window, click right, click left
	std::string a;
	std::string b;

	float xPos;
	float yPos;

	// get mouse position
	mouse->GetCursor(xPos, yPos);

	// read mouse buttons
	if (mouse->GetKeyState(Mouse::BUTTONS::BUTTON_RIGHT))
	{
		a = " <right>";
	}

	if (mouse->GetKeyState(Mouse::BUTTONS::BUTTON_LEFT))
	{
		b = " <left>";
	}

	std::string total = a + b;


	Trace::out("mouse:(%d,%d)%s \n", (int)xPos, (int)yPos, total.c_str());
}