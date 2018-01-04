#include <assert.h>
#include "Model.h"
#include "Shader.h"
#include "GraphObj_FlatTexture.h"
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"


GraphObj_FlatTexture::GraphObj_FlatTexture(Model * model, Shader * shader, TextureManager::Name name)
	: GraphicsObject(model, shader)
{
	// Is there a model and shader?
	assert(model != 0);
	assert(shader != 0);

	this->textureName = name;
}

GraphObj_FlatTexture::~GraphObj_FlatTexture()
{
}

void GraphObj_FlatTexture::SetState()
{
	// Set active texture unit for subsequent texture state calls
	glActiveTexture(GL_TEXTURE0);

	// Bind texture
	GLuint textureID = TextureManager::Find(this->textureName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_FlatTexture::SendDataToGPU()
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
}

void GraphObj_FlatTexture::Draw()
{
	// Starting point of the IBO
	glDrawElements(GL_TRIANGLES, this->GetModel()->GetNumTris() * 3, GL_UNSIGNED_INT, 0);
}

void GraphObj_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphObj_FlatTexture::DeleteGPUData()
{
	// Delete vertex array object
	this->pModel->DeleteVAO();
	// Delete program object
	this->pShader->DeleteProgram();
	// Delete vertex buffer object
	this->pModel->DeleteVBO();
}
