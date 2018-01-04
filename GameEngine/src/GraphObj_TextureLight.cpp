#include <assert.h>
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "GraphObj_TextureLight.h"

extern Heap *pHeap;

GraphObj_TextureLight::GraphObj_TextureLight(Model * model, Shader * shader, TextureManager::Name name, Vect & LightColor, Vect & LightPos)
	: GraphicsObject(model, shader), textureName(name)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);

	this->poLightColor = new(pHeap, __FILE__, __LINE__) Vect(LightColor);
	this->poLightPos = new(pHeap, __FILE__, __LINE__) Vect(LightPos);
}

GraphObj_TextureLight::~GraphObj_TextureLight()
{
	delete this->poLightColor;
	delete this->poLightPos;
}

void GraphObj_TextureLight::SetState()
{
	// Set active texture unit for subsequent texture state calls
	glActiveTexture(GL_TEXTURE0);

	// Bind texture
	GLuint textureID = TextureManager::Find(this->textureName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_TextureLight::SendDataToGPU()
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

void GraphObj_TextureLight::Draw()
{
	// Starting point of the IBO
	glDrawElements(GL_TRIANGLES, this->GetModel()->GetNumTris() * 3, GL_UNSIGNED_INT, 0);
}

void GraphObj_TextureLight::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_TextureLight::DeleteGPUData()
{
	// Delete vertex array object
	this->pModel->DeleteVAO();
	// Delete program object
	this->pShader->DeleteProgram();
	// Delete vertex buffer object
	this->pModel->DeleteVBO();
}
