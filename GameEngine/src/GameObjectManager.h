#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "PCSTree.h"

// Forward declaration
class GameObject;


// Singleton
class GameObjectManager
{
public:
	// Add GameObject to manager
	static void Add(GameObject *pGameObj);
	// Update all GameObjects
	static void Update(float currentTime);
	// Render all GameObjects
	static void Render();
	// Unload content of all GameObjects
	static void UnloadContent();
	
private:
	// Get singleton instance
	static GameObjectManager* privGetInstance();
	// No one should access this. GameObjectManager is only instantiated once.
	GameObjectManager();

	// Data
	PCSTree *pTree;
};

#endif // !GAME_OBJECT_MANAGER_H

