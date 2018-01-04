#include <assert.h>

#include "NullModel.h"
#include "Shader.h"
#include "GraphObj_Null.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "PCSTreeForwardIterator.h"

GameObjectManager::GameObjectManager()
{
	// Create null model
	NullModel *pModel = new NullModel();
	// Create null shader
	Shader *pShader = new Shader("NullShader", Shader::Name::NULL_SHADER);
	// Create null graphics object
	GraphObj_Null *pGraphObj = new GraphObj_Null(pModel, pShader);
	// Create game object
	GameObject *pGameObjRoot = new GameObject(pGraphObj);
	pGameObjRoot->SetName("GameObjectRoot"); // Set PCSNode name
	// Create tree
	this->pTree = new PCSTree();
	assert(this->pTree != 0);
	// Attach to tree
	this->pTree->Insert(pGameObjRoot, this->pTree->GetRoot());
}

void GameObjectManager::Add(GameObject * pGameObj)
{
	// Is pGameObj valid?
	assert(pGameObj != 0);

	// Get GameObjectManager instance
	GameObjectManager *pInstance = GameObjectManager::privGetInstance();

	// Attach pGameObj to root of tree
	pInstance->pTree->Insert(pGameObj, pInstance->pTree->GetRoot());
}

void GameObjectManager::Update(float currentTime)
{
	// Get manager instance
	GameObjectManager *pInstance = GameObjectManager::privGetInstance();
	// Get forward iterator from tree root node
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	// Get first node
	PCSNode *pNode = iter.First();

	// Traverse and update all GameObjects
	GameObject *pGameObj = 0;
	while (!iter.IsDone())
	{
		// Is pNode still valid?
		assert(pNode != 0);
		// Get GameObject and update it
		pGameObj = (GameObject *)pNode;
		pGameObj->Process(currentTime);

		// Move to next node
		pNode = iter.Next();
	}
}

void GameObjectManager::Render()
{
	// Get manager instance
	GameObjectManager *pInstance = GameObjectManager::privGetInstance();
	// Get forward iterator from tree root node
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	// Get first node
	PCSNode *pNode = iter.First();

	// Traverse and update all GameObjects
	GameObject *pGameObj = 0;
	while (!iter.IsDone())
	{
		// Is pNode still valid?
		assert(pNode != 0);
		// Get GameObject and update it
		pGameObj = (GameObject *)pNode;
		pGameObj->Render();

		// Move to next node
		pNode = iter.Next();
	}
}

void GameObjectManager::UnloadContent()
{
	// Get manager instance
	GameObjectManager *pInstance = GameObjectManager::privGetInstance();
	// Get forward iterator from tree root node
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	// Get first node
	PCSNode *pNode = iter.First();

	// Traverse and update all GameObjects
	GameObject *pGameObj = 0;
	while (!iter.IsDone())
	{
		// Is pNode still valid?
		assert(pNode != 0);
		// Get GameObject and update it
		pGameObj = (GameObject *)pNode;
		pGameObj->UnloadContent();

		// Move to next node
		pNode = iter.Next();
	}

	// Delete GameObject tree and all of its children
	pInstance->pTree->Remove(pInstance->pTree->GetRoot());
}

GameObjectManager * GameObjectManager::privGetInstance()
{
	// Instance of GameObjectManager is stored in BSS segment (https://en.wikipedia.org/wiki/Data_segment#BSS)
	static GameObjectManager instance;
	return &instance;
}
