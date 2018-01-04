#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "PCSTree.h"
#include "PCSTreeForwardIterator.h"
#include "MathEngine.h"

class CameraNode;
class Camera;

// Singleton
class CameraManager
{
public:
	struct Info
	{
		int windowWidth;
		int windowHeight;
		int currNumCameras;
		int totalNumCameras;
	};

public:
	static void InitManager(int windowWidth, int windowHeight);
	static void Add(const float FieldOfView_Deg, const Vect & upVect, const Vect & lookAt_pt, const Vect & pos_pt);
	static void Remove(CameraNode *pCameraNode); // Not sure when this can be used
	static void Destroy();
	static void UpdateActiveCam();
	static void CycleCamera();

	~CameraManager();

	static void SetActiveCamera(CameraNode *pCameraNode);
	static CameraNode* GetActiveCamera();

private:
	static void privCreateIterator();
	static CameraManager* privGetInstance();
	CameraManager();

	// Helper functions
	static void privIncrementCamStats();
	static void privDecrementCamStats();

	// Data
	PCSTree *pTree;
	CameraNode *pActiveCam;
	PCSTreeForwardIterator *pCycleIter;
	Info *pInfo;

};

#endif // !CAMERA_MANAGER_H

