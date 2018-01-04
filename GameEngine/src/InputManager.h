#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Mouse.h"
#include "Keyboard.h"

// Singleton
class InputManager
{
public:
	// Destructor
	~InputManager();
	// Update input states
	static void Update();
	// Initialize InputManager on GetKeyboard
	static Keyboard *GetKeyboard();
	// Initialize InputManager on GetKeyboard
	static Mouse *GetMouse();

private:
	// Get singleton instance
	static InputManager* privGetInstance();
	// Private cosntructor
	InputManager();

	// Helper functions
	static void privCameraInputUpdate();

	// Data
	Keyboard *pKey;
	Mouse    *pMouse;
	bool	 privCycleStatePrev;
	char	 pad1;
	char	 pad2;
	char	 pad3;
};

#endif // !INPUT_MANAGER_H

