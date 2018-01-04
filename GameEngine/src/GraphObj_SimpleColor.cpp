#include <sb7.h>
#include "MathEngine.h"
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "GraphObj_SimpleColor.h"

extern Heap *pHeap;

GraphObj_SimpleColor::GraphObj_SimpleColor(Model * model, Shader * shader, const Vect & colorVec)
	: GraphicsObject(model, shader)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);

	this->pColorVec = new(pHeap, __FILE__, __LINE__) Vect(colorVec);
}

GraphObj_SimpleColor::~GraphObj_SimpleColor()
{
	delete this->pColorVec;
}

void GraphObj_SimpleColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_SimpleColor::SendDataToGPU()
{
	// Set shader as active
	this->pShader->SetActiveProgram();
	// Set the VAO
	glBindVertexArray(this->GetModel()->GetVAO());

	// Get active camera
	Camera *pCamera = CameraManager::GetActiveCamera()->GetCamera();

	// Get model-view and projection matrices
	Matrix world = this->GetWorld();
	Matrix view = pCamera->getViewMatrix();
	Matrix proj = pCamera->getProjMatrix();

	// Send projection matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	// Send world matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
	// Send view matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("view_matrix"), 1, GL_FALSE, (float *)&view);

	// Send color vector to GPU
	glUniform4fv(this->pShader->GetUniformLocation("color_vector"), 1, (float *)this->pColorVec);
}

void GraphObj_SimpleColor::Draw()
{
	// Starting point of the IBO
	glDrawElements(GL_TRIANGLES, this->GetModel()->GetNumTris() * 3, GL_UNSIGNED_INT, 0);
}

void GraphObj_SimpleColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_SimpleColor::DeleteGPUData()
{
	// Delete vertex array object
	this->pModel->DeleteVAO();
	// Delete program object
	this->pShader->DeleteProgram();
	// Delete vertex buffer object
	this->pModel->DeleteVBO();
}
