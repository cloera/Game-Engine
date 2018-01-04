#include <math.h>
#include <assert.h>
#include "Trace.h"

#include "MathEngine.h"
#include "GameObject.h"

extern Heap *pHeap;

GameObject::GameObject(GraphicsObject * graphicsObj)
{
	// Is there a graphics object?
	assert(graphicsObj != 0);
	this->pGraphicsObject = graphicsObj;

	this->pWorld = new(pHeap, __FILE__, __LINE__) Matrix(MatrixSpecialType::IDENTITY);
	this->pTrans = new(pHeap, __FILE__, __LINE__) Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new(pHeap, __FILE__, __LINE__) Vect(1.0f, 1.0f, 1.0f);
	assert(this->pWorld != 0);
	assert(this->pTrans != 0);
	assert(this->pScale != 0);

	this->rotX = 0.0f;
	this->rotY = 0.0f;
	this->rotZ = 0.0f;
}

GameObject::~GameObject()
{
	delete this->pScale;
	delete this->pTrans;
	delete this->pWorld;
}

GraphicsObject * GameObject::GetGraphicsObject()
{
	return this->pGraphicsObject;
}

Matrix *GameObject::GetWorld()
{
	return this->pWorld;
}

void GameObject::SetWorld(Matrix * w)
{
	*this->pWorld = *w;
}

void GameObject::SetTranslation(const Vect & t)
{
	*this->pTrans = t;
}

void GameObject::SetRotX(const float xRot)
{
	this->rotX = xRot;
}

void GameObject::SetRotY(const float yRot)
{
	this->rotY = yRot;
}

void GameObject::SetRotZ(const float zRot)
{
	this->rotZ = zRot;
}

void GameObject::SetScale(const Vect & s)
{
	*this->pScale = s;
}

void GameObject::Update(float currentTime)
{
	// Transform world matrix
	Matrix Trans(MatrixTransType::TRANS, *this->pTrans);
	Matrix RotX(RotType::ROT_X, (currentTime * this->rotX) / MATH_180_PI);
	Matrix RotY(RotType::ROT_Y, (currentTime * this->rotY) / MATH_180_PI);
	Matrix RotZ(RotType::ROT_Z, (currentTime * this->rotZ) / MATH_180_PI);
	Matrix Scale(MatrixScaleType::SCALE, *this->pScale);

	// Set world matrix
	*this->pWorld = Scale * RotX * RotY * RotZ * Trans;
}

void GameObject::Render()
{
	assert(this->pGraphicsObject);
	this->pGraphicsObject->Render();
}

void GameObject::Process(float currentTime)
{
	this->Update(currentTime);

	assert(this->pGraphicsObject);
	this->pGraphicsObject->SetWorld(*this->pWorld);
}

void GameObject::UnloadContent()
{
	assert(this->pGraphicsObject);
	this->pGraphicsObject->UnloadContent();
}
