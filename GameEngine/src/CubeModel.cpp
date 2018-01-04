#include <assert.h>
#include <sb7.h>

#include "ModelFile.h"
#include "CubeModel.h"
#include "ModelData.h"


CubeModel::CubeModel(const char * const modelFileName)
	: Model()
{
	this->CreateModel(modelFileName);
}

CubeModel::~CubeModel()
{
}

void CubeModel::DeleteVAO()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void CubeModel::DeleteVBO()
{
	glDeleteBuffers(2, &this->VBO[0]);
}

void CubeModel::privCreateVAOToFile(const char* const modelFileName)
{
	Model::Vertice *pData;
	Model::Tri_Index *pTriList;

	this->privCreateCube(pData, pTriList);

	this->WriteModelToFile(pData, pTriList, "cube", modelFileName);

	this->privCreateVAO(pData, pTriList);
}

void CubeModel::privCreateVAOFromFile(const char * const modelFileName)
{
	Model::Vertice *data;
	Model::Tri_Index *triList;

	this->ReadModelFromFile(data, triList, modelFileName);

	this->privCreateVAO(data, triList);
}

void CubeModel::privCreateCube(Model::Vertice *& pData, Model::Tri_Index *& pTriList)
{
	// triangles on model
	this->numTris = 12;
	// vertices for every face of model
	this->numVerts = 24;

	// Create buffers for model data
	pData = new Model::Vertice[(unsigned int)this->numVerts];
	pTriList = new Model::Tri_Index[(unsigned int)this->numTris];

	unsigned int vIdx = 0;
	unsigned int triIdx = 0;

	// Back
	pData[vIdx    ].Set(-0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	pData[vIdx + 1].Set(-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f);
	pData[vIdx + 2].Set(0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f);
	pData[vIdx + 3].Set(0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx);

	vIdx += 4;
	triIdx += 2;

	// Right
	pData[vIdx    ].Set(0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 1, vIdx + 3, vIdx + 2);

	vIdx += 4;
	triIdx += 2;

	// Front
	pData[vIdx    ].Set(0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pData[vIdx + 1].Set(-0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pData[vIdx + 2].Set(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pData[vIdx + 3].Set(-0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 1, vIdx + 3, vIdx + 2);

	vIdx += 4;
	triIdx += 2;

	// Left
	pData[vIdx    ].Set(-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 1, vIdx + 3, vIdx + 2);

	vIdx += 4;
	triIdx += 2;

	// Bottom
	pData[vIdx    ].Set(-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
	pData[vIdx + 1].Set(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f);
	pData[vIdx + 2].Set(0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f);
	pData[vIdx + 3].Set(-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx);

	vIdx += 4;
	triIdx += 2;

	// Top
	pData[vIdx    ].Set(-0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	pData[vIdx + 1].Set(0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	pData[vIdx + 2].Set(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	pData[vIdx + 3].Set(-0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 2);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx);
}



