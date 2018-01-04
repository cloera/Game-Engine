#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "PCSNode.h"

class Vect;
class Camera;

class CameraNode : public PCSNode
{
public:
	CameraNode(int viewportWidth, int viewportHeight);
	CameraNode() = delete;
	~CameraNode();

	// Camera Setup
	void SetupCamera(float FieldOfView_Deg, const Vect &upVect, const Vect &lookAt_pt, const Vect &pos_pt);
	// Camera Update
	void UpdateCamera();
	// Reset Camera
	void ResetCamera();

	// Camera Movement
	void OrbitUp();
	void OrbitDown();
	void OrbitRight();
	void OrbitLeft();
	void StrafeLeft();
	void StrafeRight();
	void ZoomIn();
	void ZoomOut();

	Camera* GetCamera();

private:
	// Data
	Camera *poCamera;
	Vect   *poResetTarget;
	Vect   *poResetPosition;
	Vect   *poResetUp;
	Vect   *poCurrTarget;
};
#endif // !CAMERA_NODE_H

