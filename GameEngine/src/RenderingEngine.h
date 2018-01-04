#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H


class RenderingEngine
{
protected:
	// Derived classes should only call constructor
	RenderingEngine() {};

	// Set culling and orientation of polygons
	virtual void SetState() = 0;
	// Send uniform data to GPU
	virtual void SendDataToGPU() = 0;
	// Draw polygons
	virtual void Draw() = 0;
	// Restore culling and orientation of polygons
	virtual void RestoreState() = 0;
	// Delete VAO, VBO, and program object
	virtual void DeleteGPUData() = 0;
};

#endif // !RENDERING_ENGINE_H

