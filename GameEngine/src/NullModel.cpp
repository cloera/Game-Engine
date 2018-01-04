#include "NullModel.h"

NullModel::NullModel() : Model()
{
	// Just call default Model constructor
}

NullModel::~NullModel()
{
	// Nothing to do
}

void NullModel::DeleteVAO()
{
	// Nothing to do
}

void NullModel::DeleteVBO()
{
	// Nothing to do
}

void NullModel::privCreateVAO(Model::Vertice *, Model::Tri_Index *)
{
	// Nothing to do
}

void NullModel::privCreateVAOToFile(const char * const)
{
	// Nothing to do
}

void NullModel::privCreateVAOFromFile(const char* const)
{
	// Nothing to do here
}
