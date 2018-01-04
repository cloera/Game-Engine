#ifndef GRAPH_OBJ_NULL_H
#define GRAPH_OBJ_NULL_H

#include "GraphicsObject.h"

class GraphObj_Null : public GraphicsObject
{
public:
	// Specialized constructor
	GraphObj_Null(Model *model, Shader *shader);
	// Destructor
	~GraphObj_Null();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();
};

#endif // !GRAPH_OBJ_NULL_H

