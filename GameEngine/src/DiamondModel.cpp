#include <assert.h>
#include <sb7.h>

#include "ModelFile.h"
#include "DiamondModel.h"


DiamondModel::DiamondModel(const char * const modelFileName)
	: Model()
{
	this->CreateModel(modelFileName);
}

DiamondModel::~DiamondModel()
{
}

void DiamondModel::DeleteVAO()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void DiamondModel::DeleteVBO()
{
	glDeleteBuffers(2, &this->VBO[0]);
}

void DiamondModel::privCreateVAOToFile(const char * const modelFileName)
{
	Model::Vertice *pData;
	Model::Tri_Index *pTriList;

	this->privCreateDiamond(pData, pTriList);

	this->WriteModelToFile(pData, pTriList, "diamond", modelFileName);

	this->privCreateVAO(pData, pTriList);
}

void DiamondModel::privCreateVAOFromFile(const char * const modelFileName)
{
	Model::Vertice *data;
	Model::Tri_Index *triList;

	this->ReadModelFromFile(data, triList, modelFileName);

	this->privCreateVAO(data, triList);
}

void DiamondModel::privCreateDiamond(Model::Vertice *& pData, Model::Tri_Index *& pTriList)
{
	// 6 triangles on pyramid
	this->numTris = 8;
	// 3 vertices for every face of pyramid
	this->numVerts = this->numTris * 2;

	// Create buffers for model data
	pData = new Model::Vertice[(unsigned int)this->numVerts];
	pTriList = new Model::Tri_Index[(unsigned int)this->numTris];

	Vect normal;
	unsigned int vIdx = 0;
	unsigned int triIdx = 0;

	// Front
	pData[vIdx].Set(0.0f, 0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(0.0f, -0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	normal = this->CalcPolygonNormal(pData[vIdx].GetPos(), pData[vIdx + 1].GetPos(), pData[vIdx + 3].GetPos());
	pData[vIdx].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 1].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 2].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 3].SetNormal(normal.x(), normal.y(), normal.z());

	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 3);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx + 1);

	vIdx += 4;
	triIdx += 2;

	// Back
	pData[vIdx].Set(0.0f, 0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(-0.25f, 0.0f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(0.0f, -0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	normal = this->CalcPolygonNormal(pData[vIdx].GetPos(), pData[vIdx + 1].GetPos(), pData[vIdx + 3].GetPos());
	pData[vIdx].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 1].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 2].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 3].SetNormal(normal.x(), normal.y(), normal.z());

	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 3);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx + 1);

	vIdx += 4;
	triIdx += 2;

	// Left
	pData[vIdx].Set(0.0f, 0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(-0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(0.0f, -0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(-0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	normal = this->CalcPolygonNormal(pData[vIdx].GetPos(), pData[vIdx + 1].GetPos(), pData[vIdx + 3].GetPos());
	pData[vIdx].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 1].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 2].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 3].SetNormal(normal.x(), normal.y(), normal.z());

	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 3);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx + 1);

	vIdx += 4;
	triIdx += 2;

	// Right
	pData[vIdx].Set(0.0f, 0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 1].Set(0.25f, 0.0f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 2].Set(0.0f, -0.25f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	pData[vIdx + 3].Set(0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	normal = this->CalcPolygonNormal(pData[vIdx].GetPos(), pData[vIdx + 1].GetPos(), pData[vIdx + 3].GetPos());
	pData[vIdx].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 1].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 2].SetNormal(normal.x(), normal.y(), normal.z());
	pData[vIdx + 3].SetNormal(normal.x(), normal.y(), normal.z());

	pTriList[triIdx].Set(vIdx, vIdx + 1, vIdx + 3);
	pTriList[triIdx + 1].Set(vIdx + 2, vIdx + 3, vIdx + 1);

	vIdx += 4;
	triIdx += 2;
}
