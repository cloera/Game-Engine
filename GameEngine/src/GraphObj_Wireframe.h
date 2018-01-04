#ifndef GRAPH_OBJ_WIREFRAME_H
#define GRAPH_OBJ_WIREFRAME_H

#include "GraphicsObject.h"

class GraphObj_Wireframe : public GraphicsObject
{
public:
	GraphObj_Wireframe(Model *model, Shader *shader);
	~GraphObj_Wireframe();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();
};

#endif // !GRAPH_OBJ_WIREFRAME_H

