#include <assert.h>
#include "GraphicsObject.h"
#include "Model.h"
#include "Shader.h"

extern Heap *pHeap;

GraphicsObject::GraphicsObject(Model * model, Shader * shader)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);

	this->pModel = model;
	this->pShader = shader;

	this->pWorld = new(pHeap, __FILE__, __LINE__) Matrix(MatrixSpecialType::IDENTITY);
}

GraphicsObject::~GraphicsObject()
{
	delete this->pWorld;
}

void GraphicsObject::Render()
{
	// Set culling and orientation of polygons
	this->SetState();
	// Send uniform data to GPU
	this->SendDataToGPU();
	// Draw polygons
	this->Draw();
	// Restore culling and orientation of polygons
	this->RestoreState();
}

void GraphicsObject::UnloadContent()
{
	// Delete VAO, VBO, and program object
	this->DeleteGPUData();
}

void GraphicsObject::SetWorld(Matrix & world)
{
	this->pWorld = &world;
}

Model * GraphicsObject::GetModel()
{
	return this->pModel;
}

Matrix & GraphicsObject::GetWorld()
{
	return *this->pWorld;
}
