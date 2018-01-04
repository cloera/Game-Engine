#ifndef GRAPH_OBJ_TEXTURE_LIGHT_H
#define GRAPH_OBJ_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "TextureManager.h"

class GraphObj_TextureLight : public GraphicsObject
{
public:
	GraphObj_TextureLight(Model *model, Shader *shader, TextureManager::Name name,
						 Vect &LightColor, Vect &LightPos);
	GraphObj_TextureLight() = delete;
	~GraphObj_TextureLight();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();

	// Uniform Data
	TextureManager::Name textureName;
	Vect *poLightColor;
	Vect *poLightPos;
};


#endif // !GRAPH_OBJ_TEXTURE_LIGHT_H

