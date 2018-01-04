#include <assert.h>
#include "MathEngine.h"
#include "Camera.h"
#include "CameraNode.h"

extern Heap *pHeap;

CameraNode::CameraNode(int viewportWidth, int viewportHeight)
{
	this->poCamera = new(pHeap, __FILE__, __LINE__) Camera();
	this->poCamera->setViewport(0, 0, viewportWidth, viewportHeight);

	this->poCurrTarget = new(pHeap, __FILE__, __LINE__) Vect();
	this->poResetTarget = new(pHeap, __FILE__, __LINE__) Vect();
	this->poResetPosition = new(pHeap, __FILE__, __LINE__) Vect();
	this->poResetUp = new(pHeap, __FILE__, __LINE__) Vect();
}

CameraNode::~CameraNode()
{
	delete this->poCamera;
	delete this->poCurrTarget;
	delete this->poResetTarget;
	delete this->poResetPosition;
	delete this->poResetUp;
}

void CameraNode::SetupCamera(float FieldOfView_Deg, const Vect & upVect, const Vect & lookAt_pt, const Vect & pos_pt)
{
	float aspectRatio = float(this->poCamera->getScreenWidth()) / float(this->poCamera->getScreenHeight());

	this->poCamera->setPerspective(FieldOfView_Deg, aspectRatio, 0.10f, 1000.0f);
	this->poCamera->setOrientAndPosition(upVect, lookAt_pt, pos_pt);

	*this->poResetUp = upVect;
	*this->poResetTarget = lookAt_pt;
	*this->poResetPosition = pos_pt;
}

void CameraNode::UpdateCamera()
{
	this->poCamera->updateCamera();
}

void CameraNode::ResetCamera()
{
	assert(this->poResetTarget != 0);
	assert(this->poResetPosition != 0);
	assert(this->poResetUp != 0);

	this->poCamera->setHelper(*this->poResetUp, *this->poResetTarget, *this->poResetPosition);
	*this->poCurrTarget = *this->poResetTarget;
}

void CameraNode::OrbitUp()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	// Set target
	tar = *this->poCurrTarget;

	Matrix Trans(TRANS, tar);
	Matrix NegTrans(TRANS, -tar);
	Matrix Rot;
	Rot.set(rightNorm, -0.01f);

	Matrix M = NegTrans * Rot * Trans;

	up = up * M;
	pos = pos * M;
	tar = tar * M;

	this->poCamera->setHelper(up, tar, pos);
}

void CameraNode::OrbitDown()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	// Set target
	tar = *this->poCurrTarget;

	Matrix Trans(TRANS, tar);
	Matrix NegTrans(TRANS, -tar);
	Matrix Rot;
	Rot.set(rightNorm, 0.01f);

	Matrix M = NegTrans * Rot * Trans;

	up = up * M;
	pos = pos * M;
	tar = tar * M;

	this->poCamera->setHelper(up, tar, pos);
}

void CameraNode::OrbitRight()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	// Set target
	tar = *this->poCurrTarget;

	Matrix Trans(TRANS, tar);
	Matrix NegTrans(TRANS, -tar);
	Matrix Rot;
	Rot.set(upNorm, +0.01f);

	Matrix M = NegTrans * Rot * Trans;

	up = up * M;
	pos = pos * M;
	tar = tar * M;

	this->poCamera->setHelper(up, tar, pos);
}

void CameraNode::OrbitLeft()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	// Set target
	tar = *this->poCurrTarget;

	Matrix Trans(TRANS, tar);
	Matrix NegTrans(TRANS, -tar);
	Matrix Rot;
	Rot.set(upNorm, -0.01f);

	Matrix M = NegTrans * Rot * Trans;

	up = up * M;
	pos = pos * M;
	tar = tar * M;

	this->poCamera->setHelper(up, tar, pos);
}

void CameraNode::StrafeLeft()
{
	Vect up;
	Vect tar;
	Vect pos;

	this->poCamera->getLookAt(tar);
	this->poCamera->getUp(up);
	this->poCamera->getPos(pos);

	Vect vPos2 = pos;
	Vect vLookAt2 = tar;

	vPos2[x] -= 0.04f;
	vLookAt2[x] -= 0.04f;

	*this->poCurrTarget = vLookAt2;
	
	this->poCamera->setOrientAndPosition(up, vLookAt2, vPos2);
}

void CameraNode::StrafeRight()
{
	Vect up;
	Vect tar;
	Vect pos;

	this->poCamera->getLookAt(tar);
	this->poCamera->getUp(up);
	this->poCamera->getPos(pos);

	Vect vPos2 = pos;
	Vect vLookAt2 = tar;
	
	vPos2[x] += 0.04f;
	vLookAt2[x] += 0.04f;

	*this->poCurrTarget = vLookAt2;
	
	this->poCamera->setOrientAndPosition(up, vLookAt2, vPos2);
}

void CameraNode::ZoomIn()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	pos = pos + 0.02f * forwardNorm;
	tar = tar + 0.02f * forwardNorm;

	if (pos[z] > 0.5f)
	{
		this->poCamera->setHelper(up, tar, pos);
	}
}

void CameraNode::ZoomOut()
{
	// 3 points - Position, Target, Up
	Vect pos, tar, up;
	// 3 normals - Up normal, Forward normal, Right normal
	Vect upNorm, forwardNorm, rightNorm;

	this->poCamera->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	// Set target
	tar = *this->poCurrTarget;

	pos = pos - 0.02f * forwardNorm;

	this->poCamera->setHelper(up, tar, pos);
}

Camera * CameraNode::GetCamera()
{
	return this->poCamera;
}
