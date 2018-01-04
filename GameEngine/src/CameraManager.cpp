#include <assert.h>
#include "Camera.h"
#include "CameraNode.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	this->pTree = new PCSTree();
	assert(this->pTree != 0);

	this->pActiveCam = 0;
	this->pCycleIter = 0;

	this->pInfo = new Info();
	this->pInfo->currNumCameras = 0;
	this->pInfo->totalNumCameras = 0;
	this->pInfo->windowHeight = 0;
	this->pInfo->windowWidth = 0;
}

CameraManager::~CameraManager()
{
	delete this->pTree;
	delete this->pInfo;
}

void CameraManager::privIncrementCamStats()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Update stats
	pInstance->pInfo->currNumCameras++;
	if (pInstance->pInfo->currNumCameras > pInstance->pInfo->totalNumCameras)
	{
		pInstance->pInfo->totalNumCameras++;
	}
}

void CameraManager::privDecrementCamStats()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Update stats
	pInstance->pInfo->currNumCameras--;
}

void CameraManager::InitManager(int windowWidth, int windowHeight)
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	pInstance->pInfo->windowWidth = windowWidth;
	pInstance->pInfo->windowHeight = windowHeight;
}

void CameraManager::Add(const float FieldOfView_Deg, const Vect & upVect, const Vect & lookAt_pt, const Vect & pos_pt)
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Create CameraNode
	int height = pInstance->pInfo->windowHeight;
	int width = pInstance->pInfo->windowWidth;
	CameraNode *pCameraNode = new CameraNode(width, height);
	assert(pCameraNode != 0);

	// Setup camera
	pCameraNode->SetupCamera(FieldOfView_Deg, upVect, lookAt_pt, pos_pt);

	// Update camera
	pCameraNode->UpdateCamera();

	// Make camera active
	pInstance->SetActiveCamera(pCameraNode);

	// Add camera to manager
	pInstance->pTree->Insert(pCameraNode, pInstance->pTree->GetRoot());

	// Update stats
	pInstance->privIncrementCamStats();
}

void CameraManager::Remove(CameraNode * pCameraNode)
{
	// Is CameraNode valid?
	assert(pCameraNode != 0);

	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Create iterator
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	PCSNode *pNode = iter.First();

	// Loop through tree and find node to remove
	CameraNode *pCam = 0;
	while (!iter.IsDone())
	{
		assert(pNode != 0);
		pCam = (CameraNode *)pNode;
		// If this is the node we're looking for
		if (pCam == pCameraNode)
		{
			// Break. We found it
			break;
		}
		// Move to next node
		pNode = iter.Next();
	}

	// Remove camera from tree
	pInstance->pTree->Remove(pNode);

	// Update stats
	pInstance->privDecrementCamStats();
}

void CameraManager::Destroy()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Destroy entire tree
	pInstance->pTree->Remove(pInstance->pTree->GetRoot());
}

void CameraManager::UpdateActiveCam()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();
	// Is active camera valid?
	assert(pInstance->pActiveCam != 0);

	// Update active camera
	pInstance->pActiveCam->UpdateCamera();
}

void CameraManager::CycleCamera()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	CameraNode *pCurrCam = 0;

	// If iterator is null
	if (pInstance->pCycleIter == 0)
	{
		// Create iterator
		CameraManager::privCreateIterator();
	}

	// Move to next node in tree
	pInstance->pCycleIter->Next();

	// If iterator is done
	if (pInstance->pCycleIter->IsDone())
	{
		assert(pInstance->pTree->GetRoot() != 0);
		// Start iterator from beginning
		PCSTreeForwardIterator newIter(pInstance->pTree->GetRoot());
		*pInstance->pCycleIter = newIter;
		// Get camera node
		pCurrCam = (CameraNode *)pInstance->pCycleIter->First();
		// Reset camera
		pCurrCam->ResetCamera();
		// Set active camera to first camera
		pInstance->SetActiveCamera(pCurrCam);
	}
	// Else
	else
	{
		// Get camera node
		pCurrCam = (CameraNode *)pInstance->pCycleIter->CurrentItem();
		// Reset camera
		pCurrCam->ResetCamera();
		// Set active camera to current node
		pInstance->SetActiveCamera(pCurrCam);
	}
}

void CameraManager::SetActiveCamera(CameraNode * pCameraNode)
{
	// Is CameraNode valid?
	assert(pCameraNode != 0);

	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Set active camera
	pInstance->pActiveCam = pCameraNode;
}

CameraNode * CameraManager::GetActiveCamera()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();
	// Is active camera valid?
	assert(pInstance->pActiveCam != 0);

	return pInstance->pActiveCam;
}

void CameraManager::privCreateIterator()
{
	// Get manager instance
	CameraManager *pInstance = CameraManager::privGetInstance();

	// Get root node
	PCSNode *pRoot = pInstance->pTree->GetRoot();
	assert(pRoot != 0);

	// Set iterator to root node
	pInstance->pCycleIter = new PCSTreeForwardIterator(pRoot);
	//PCSNode *pNode = pInstance->pCycleIter->First();

	//CameraNode *pCurrCam = 0;

	//// While iterator is not done
	//while (!pInstance->pCycleIter->IsDone())
	//{
	//	assert(pNode != 0);
	//	pCurrCam = (CameraNode *)pNode;

	//	// If active camera == current iterator item
	//	if (pInstance->pActiveCam == pCurrCam)
	//	{
	//		// Moved iterator to current active camera. Break.
	//		break;
	//	}
	//			
	//	// Move to next node
	//	pNode = pInstance->pCycleIter->Next();
	//}
}

CameraManager * CameraManager::privGetInstance()
{
	// Instance of CameraManager is stored in BSS segment (https://en.wikipedia.org/wiki/Data_segment#BSS)
	static CameraManager instance;
	return &instance;
}

