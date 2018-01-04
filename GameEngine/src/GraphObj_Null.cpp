#include "GraphObj_Null.h"

GraphObj_Null::GraphObj_Null(Model * model, Shader * shader)
	: GraphicsObject(model, shader)
{
	// Just pass arguments to GraphicsObject constructor
}

GraphObj_Null::~GraphObj_Null()
{
	// Nothing to do
}

void GraphObj_Null::SetState()
{
	// Nothing to do
}

void GraphObj_Null::SendDataToGPU()
{
	// Nothing to do
}

void GraphObj_Null::Draw()
{
	// Nothing to do
}

void GraphObj_Null::RestoreState()
{
	// Nothing to do
}

void GraphObj_Null::DeleteGPUData()
{
	// Nothing to do
}
