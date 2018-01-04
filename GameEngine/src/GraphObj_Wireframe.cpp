#include <assert.h>
#include "Model.h"
#include "Shader.h"
#include "GraphObj_Wireframe.h"
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"


GraphObj_Wireframe::GraphObj_Wireframe(Model * model, Shader * shader)
	: GraphicsObject(model, shader)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);
}

GraphObj_Wireframe::~GraphObj_Wireframe()
{
}

void GraphObj_Wireframe::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_Wireframe::SendDataToGPU()
{
	// Set shader as active
	this->pShader->SetActiveProgram();
	// Set the VAO
	glBindVertexArray(this->GetModel()->GetVAO());

	// Change state to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

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
}

void GraphObj_Wireframe::Draw()
{
	// Starting point of the IBO
	glDrawElements(GL_TRIANGLES, this->GetModel()->GetNumTris() * 3, GL_UNSIGNED_INT, 0);
}

void GraphObj_Wireframe::RestoreState()
{
	// Change state to fill wireframe with color on both sides
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphObj_Wireframe::DeleteGPUData()
{
	// Delete vertex array object
	this->pModel->DeleteVAO();
	// Delete program object
	this->pShader->DeleteProgram();
	// Delete vertex buffer object
	this->pModel->DeleteVBO();
}
