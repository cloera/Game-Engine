#include <assert.h>
#include "CameraManager.h"
#include "CameraNode.h"
#include "InputManager.h"

InputManager::InputManager()
{
	this->pKey = new Keyboard();
	assert(this->pKey != 0);

	this->pMouse = new Mouse();
	assert(this->pMouse != 0);

	this->privCycleStatePrev = false;
	this->pad1 = 0;
	this->pad2 = 0;
	this->pad3 = 0;
}

InputManager::~InputManager()
{
	delete this->pKey;
}

void InputManager::Update()
{
	// Check for Camera movement updates
	InputManager::privCameraInputUpdate();
}

void InputManager::privCameraInputUpdate()
{
	InputManager *pInstance = InputManager::privGetInstance();
	Keyboard *pKeyboard = pInstance->pKey;

	CameraNode *pCamNode = CameraManager::GetActiveCamera();

	bool cycleStateCurr = pKeyboard->GetKeyState(Keyboard::KEYS::KEY_C);
	// If KEY_C was pressed and this is the first time it is pressed
	if (cycleStateCurr == true && pInstance->privCycleStatePrev == false)
	{
		// Cycle to next camera in manager
		CameraManager::CycleCamera();
	}
	// Store current state in previous state
	pInstance->privCycleStatePrev = cycleStateCurr;

	// Orbit camera up
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_ARROW_UP) == true)
	{
		pCamNode->OrbitUp();
	}
	// Orbit camera down
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_ARROW_DOWN) == true)
	{
		pCamNode->OrbitDown();
	}
	// Orbit camera right
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_ARROW_RIGHT) == true)
	{
		pCamNode->OrbitRight();
	}
	// Orbit camera left
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_ARROW_LEFT) == true)
	{
		pCamNode->OrbitLeft();
	}
	// Zoom in camera
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_W) == true)
	{
		pCamNode->ZoomIn();
	}
	// Zoom out camera
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_S) == true)
	{
		pCamNode->ZoomOut();
	}
	// Strafe camera right
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_D) == true)
	{
		pCamNode->StrafeRight();
	}
	// Strafe camera left
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_A) == true)
	{
		pCamNode->StrafeLeft();
	}
}

Keyboard * InputManager::GetKeyboard()
{
	InputManager *pInstance = InputManager::privGetInstance();
	return pInstance->pKey;
}

Mouse * InputManager::GetMouse()
{
	InputManager *pInstance = InputManager::privGetInstance();
	return pInstance->pMouse;
}

InputManager * InputManager::privGetInstance()
{
	// Instance of TextureManager is stored in BSS segment (https://en.wikipedia.org/wiki/Data_segment#BSS)
	static InputManager instance;
	return &instance;
}
