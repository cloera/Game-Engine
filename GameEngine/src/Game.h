#ifndef GAME_H
#define GAME_H

#include "Engine.h"

#include <sb7.h>
#include <math.h>

#include <vmath.h>
// ToDo get rid of the projection, move to the camera

#include "MathEngine.h"

class Game : public Engine
{
public:
	// constructor
	Game(const char* windowName, const int Width, const int Height);
	~Game();

    void Initialize();
    virtual void LoadContent();
	virtual void Update(float currentTime);
    virtual void Render();
    virtual void UnLoadContent();
	virtual void ClearBuffer();

    void OnResize(int w, int h);


	// Data

};

#endif
