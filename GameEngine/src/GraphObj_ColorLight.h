#ifndef GRAPH_OBJ_COLOR_LIGHT_H
#define GRAPH_OBJ_COLOR_LIGHT_H


#include "GraphicsObject.h"

class GraphObj_ColorLight : public GraphicsObject
{
public:
	GraphObj_ColorLight(Model *model, Shader *shader, const Vect &lightPos, const Vect &lightColor);
	GraphObj_ColorLight() = delete;
	~GraphObj_ColorLight();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();

	// Uniform Data
	Vect *poLightColor;
	Vect *poLightPos;
};

#endif // !GRAPH_OBJ_COLOR_LIGHT_H

