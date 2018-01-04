#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"

#include "RenderingEngine.h"
class Model;
class Shader;

class GraphicsObject : private RenderingEngine
{
public:
	// Specialized constructor
	GraphicsObject(Model *model, Shader *shader);

	// Constructor
	GraphicsObject() = delete;
	// Destructor (virtual for derived classes)
	virtual ~GraphicsObject();

	// Render graphics object to window
	void Render();
	// Unload graphics object
	void UnloadContent();

	// Setters and Getters
	void	SetWorld(Matrix & world);
	Model*  GetModel();
	Matrix& GetWorld();

protected:
	// Data
	Matrix *pWorld;
	Model  *pModel;
	Shader *pShader;
};

#endif // !GRAPHICS_OBJECT_H

