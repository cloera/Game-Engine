#ifndef GRAPH_OBJ_SIMPLE_COLOR_H
#define GRAPH_OBJ_SIMPLE_COLOR_H

#include "GraphicsObject.h"

class GraphObj_SimpleColor : public GraphicsObject
{
public:
	GraphObj_SimpleColor(Model *model, Shader *shader, const Vect &colorVec);
	GraphObj_SimpleColor() = delete;
	~GraphObj_SimpleColor();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();

	// Uniform Data
	Vect *pColorVec;
};
#endif // !GRAPH_OBJ_SIMPLE_COLOR_H

