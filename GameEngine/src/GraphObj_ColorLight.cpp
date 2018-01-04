#include <assert.h>
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "GraphObj_ColorLight.h"

extern Heap *pHeap;

GraphObj_ColorLight::GraphObj_ColorLight(Model * model, Shader * shader, const Vect & lightPos, const Vect & lightColor)
	: GraphicsObject(model, shader)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);

	this->poLightPos = new(pHeap, __FILE__, __LINE__) Vect(lightPos);
	this->poLightColor = new(pHeap, __FILE__, __LINE__) Vect(lightColor);
}

GraphObj_ColorLight::~GraphObj_ColorLight()
{
	delete this->poLightPos;
	delete this->poLightColor;
}

void GraphObj_ColorLight::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_ColorLight::SendDataToGPU()
{
	// Set shader as active
	this->pShader->SetActiveProgram();
	// Set the VAO
	glBindVertexArray(this->GetModel()->GetVAO());

	// Get active camera
	Camera *pCamera = CameraManager::GetActiveCamera()->GetCamera();

	// Get world, view, and projection matrices
	Matrix world = this->GetWorld();
	Matrix view = pCamera->getViewMatrix();
	Matrix proj = pCamera->getProjMatrix();

	// Send projection matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	// Send view matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	// Send world matrix to GPU
	glUniformMatrix4fv(this->pShader->GetUniformLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	// Send light position vector to GPU
	glUniform3fv(this->pShader->GetUniformLocation("vLightPos"), 1, (float *)this->poLightPos);
	// Send light color vector to GPU
	glUniform4fv(this->pShader->GetUniformLocation("vColor"), 1, (float *)this->poLightColor);
}

void GraphObj_ColorLight::Draw()
{
	// Starting point of the IBO
	glDrawElements(GL_TRIANGLES, this->GetModel()->GetNumTris() * 3, GL_UNSIGNED_INT, 0);
}

void GraphObj_ColorLight::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_ColorLight::DeleteGPUData()
{
	// Delete vertex array object
	this->pModel->DeleteVAO();
	// Delete program object
	this->pShader->DeleteProgram();
	// Delete vertex buffer object
	this->pModel->DeleteVBO();
}
