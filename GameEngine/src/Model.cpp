#include <assert.h>
#include "File.h"

#include "ModelFile.h"
#include "Model.h"

Model::Model()
{
	this->numVerts = 0;
	this->numTris = 0;
	this->VAO = 0;
	this->VBO[0] = 0;
	this->VBO[1] = 0;
}

Model::~Model()
{
}

int Model::GetNumVerts()
{
	return this->numVerts;
}

int Model::GetNumTris()
{
	return this->numTris;
}

GLuint Model::GetVAO()
{
	return this->VAO;
}

void Model::CreateModel(const char * const modelFileName)
{
	bool hasFile = this->CheckForModelFile(modelFileName);

	if (hasFile)
	{
		// There's a file. Read model from file and create VAO
		this->privCreateVAOFromFile(modelFileName);
	}
	else
	{
		// No model file. Write model to file and create VAO
		this->privCreateVAOToFile(modelFileName);
	}
}

void Model::privCreateVAO(Model::Vertice * modelData, Model::Tri_Index * triList)
{
	// Create an array handle
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO != 0);
	glBindVertexArray(this->VAO);

	// Create a buffer handle
	glGenBuffers(2, &this->VBO[0]);
	assert(this->VBO != 0);

	/******************** Load combined data ***************************/

	// Bind model data to 1st buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);

	// Load data to GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Model::Vertice) * this->numVerts), modelData, GL_STATIC_DRAW);

	// define an array of generic vertex attribute data
	// Vert data is location: 0  (used in vertex shader)
	void *offsetVert = (void *)((unsigned int)&modelData[0].x - (unsigned int)modelData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Model::Vertice), offsetVert);
	// Enable generic attribute array
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void *offsetTex = (void *)((unsigned int)&modelData[0].u - (unsigned int)modelData);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Model::Vertice), offsetTex);
	// Enable generic attribute array
	glEnableVertexAttribArray(1);

	// Normals data is location: 2  (used in vertex shader)
	void *offsetNorm = (void *)((unsigned int)&modelData[0].nx - (unsigned int)modelData);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Model::Vertice), offsetNorm);
	// Enable generic attribute array
	glEnableVertexAttribArray(2);

	/******************** Load index data ***************************/

	// Bind index data to 2nd buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO[1]);

	// Copy index data to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(this->numTris * sizeof(Model::Tri_Index)), triList, GL_STATIC_DRAW);
}

void Model::privCreateVAOFromFile(const char * const)
{
	/****** Do NOT call this ******/
	/****** Implement this in derived class *******/
	assert(false);
}

void Model::WriteModelToFile(Vertice *modelData, Tri_Index *triList, const char * const modelName, const char * const modelFileName)
{
	// create a header
	ModelFile modelHdr;

	// object name
	strncpy_s(modelHdr.modelName, MODEL_NAME_SIZE, modelName, _TRUNCATE);

	// vertex buffer
	modelHdr.numVerts = this->numVerts;
	modelHdr.vertBufferOffset = 0;

	// trilist index 
	modelHdr.numTriList = this->numTris;
	modelHdr.triListBufferOffset = 0;


	/***************** Write the data to a file *********************/

	File::Handle fh;
	File::Error  ferror;

	//----------- WRITE ------------------------------------------
	ferror = File::Open(fh, modelFileName, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	// write the Header
	ferror = File::Write(fh, &modelHdr, sizeof(ModelFile));
	assert(ferror == File::Error::SUCCESS);

	// write the vert buffer data
	ferror = File::Tell(fh, modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, modelData, sizeof(Model::Vertice) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// write the index buffer
	ferror = File::Tell(fh, modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, triList, sizeof(Model::Tri_Index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	// Finish the write
	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// Rewind and overwrite model hdr
	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &modelHdr, sizeof(ModelFile));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// VERIFY
	ModelFile modelHdr2;

	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &modelHdr2, sizeof(ModelFile));
	assert(ferror == File::Error::SUCCESS);

	// CLOSE
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);
}

void Model::ReadModelFromFile(Vertice *& modelData, Tri_Index *& triList, const char * const modelFileName)
{
	File::Handle fh;
	File::Error  ferror;

	ferror = File::Open(fh, modelFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Read the Hdr
	ModelFile modelHdr;
	ferror = File::Read(fh, &modelHdr, sizeof(ModelFile));
	assert(ferror == File::Error::SUCCESS);

	// Using the hdr, allocate the space for the buffers
	this->numVerts = modelHdr.numVerts;
	this->numTris = modelHdr.numTriList;

	// allocate buffers --- LEAKING MEMORY
	modelData = new Model::Vertice[(unsigned int)modelHdr.numVerts];
	triList = new Model::Tri_Index[(unsigned int)modelHdr.numTriList];

	// Read verts
	ferror = File::Seek(fh, File::Location::BEGIN, (int)modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, modelData, sizeof(Model::Vertice) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh, File::Location::BEGIN, (int)modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, triList, sizeof(Model::Tri_Index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

}

bool Model::CheckForModelFile(const char * const modelFileName)
{
	File::Handle fh;
	File::Error ferror;
	bool hasFile;

	ferror = File::Open(fh, modelFileName, File::Mode::READ);
	if (ferror == File::Error::OPEN_FAIL)
	{
		hasFile = false;
	}
	else
	{
		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		hasFile = true;
	}

	return hasFile;
}

Vect Model::CalcPolygonNormal(const Vect & vert1, const Vect & vert2, const Vect & vert3)
{
	Vect vect1 = vert1 - vert3;
	Vect vect2 = vert1 - vert2;
	return vect1.cross(vect2).getNorm();
}
