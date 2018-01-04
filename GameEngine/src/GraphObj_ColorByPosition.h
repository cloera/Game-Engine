#ifndef GRAPH_OBJ_COLOR_BY_POSITION_H
#define GRAPH_OBJ_COLOR_BY_POSITION_H

#include "GraphicsObject.h"

class GraphObj_ColorByPosition : public GraphicsObject
{
public:
	// Specialized constructor
	GraphObj_ColorByPosition(Model *model, Shader *shader);
	// Destructor
	~GraphObj_ColorByPosition();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();
};

#endif // !GRAPH_OBJ_COLOR_BY_POSITION_H

