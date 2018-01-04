#ifndef GRAPH_OBJ_FLAT_TEXTURE_H
#define GRAPH_OBJ_FLAT_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureManager.h"

class GraphObj_FlatTexture : public GraphicsObject
{
public:
	GraphObj_FlatTexture(Model *model, Shader *shader, TextureManager::Name name);
	~GraphObj_FlatTexture();

	// RenderingEngine function implementations
	void SetState();
	void SendDataToGPU();
	void Draw();
	void RestoreState();
	void DeleteGPUData();

	// Uniform Data
	TextureManager::Name textureName;
};


#endif // !GRAPH_OBJ_FLAT_TEXTURE_H

