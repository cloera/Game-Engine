#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "PCSNode.h"

#include "Shader.h"
#include "Model.h"
#include "GraphicsObject.h"

class GameObject : public PCSNode
{
public:
	// Specialized constructor
	GameObject(GraphicsObject *graphicsObj);

	// Big Four constructors
	GameObject() = delete;
	GameObject(const GameObject &in) = delete;
	GameObject & operator=(const GameObject &in) = delete;
	virtual ~GameObject();

	// Update GameObject every frame
	void Update(float currentTime);
	// Render GraphicsObject to screen
	void Render();
	// Process the GraphicsObject every frame
	void Process(float currentTime);
	// Unload GraphicsObject
	void UnloadContent();

	// Getters
	GraphicsObject* GetGraphicsObject();
	Matrix* GetWorld();

	// Setters
	void SetWorld(Matrix *w);
	void SetTranslation(const Vect &t);
	void SetRotX(const float xRot);
	void SetRotY(const float yRot);
	void SetRotZ(const float zRot);
	void SetScale(const Vect &s);

protected:
	Matrix *pWorld;

private:
	GraphicsObject *pGraphicsObject;
	Vect *pTrans;
	Vect *pScale;
	float rotX;
	float rotY;
	float rotZ;
};



#endif