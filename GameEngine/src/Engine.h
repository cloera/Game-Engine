
#ifndef ENGINE_H
#define ENGINE_H

#ifdef WIN32
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#else
#include <unistd.h>
#define Sleep(t) sleep(t)
#endif

#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include "GLFW/glfw3.h"

#include "sb7ext.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define UNUSED_VAR(x) (void)x // Keenan


class Engine
{
public:
	// Specialized constructor
	Engine(const char* windowName, const int Width, const int Height);
	// Destructor
	virtual ~Engine();
	
	// Engine Loop
	void Run();
	
	// Functions for derived Game class
	virtual void Initialize();
	virtual void LoadContent() = 0;
	virtual void Update(float currentTime) = 0;
	virtual void Render() = 0;
	virtual void UnLoadContent();

	// optional overloading
	virtual void ClearBuffer();

	// Input state
	int GetKey(int key);
	int GetMouseButton(int key);

	// On event functions called within GLFW callback functions
	void SetWindowTitle(const char * title);
	virtual void OnResize(int w, int h);
	virtual void OnKey(int key, int action);
	virtual void OnMouseButton(int button, int action);
	virtual void OnMouseMove(int x, int y);
	virtual void OnMouseWheel(int pos);
	virtual void OnDebugMessage(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message);
	void GetMousePosition(int& x, int& y);
	void GetMousePosition(float& x, float& y);

	// Settings for Engine
	struct APPINFO
	{
		char title[128];
		int windowWidth;
		int windowHeight;
		int majorVersion;
		int minorVersion;
		int samples;
		union
		{
			struct
			{
				unsigned int    fullscreen : 1;
				unsigned int    vsync : 1;
				unsigned int    cursor : 1;
				unsigned int    stereo : 1;
				unsigned int    debug : 1;
				unsigned int    robust : 1;
			};
			unsigned int        all;
		} flags;
	};

protected:
	// Protected data
	APPINFO     info;
	static      Engine * pApp;
	GLFWwindow* window;

	// GLFW callback functions
	static void GLFW_OnResize(GLFWwindow* window, int w, int h);
	static void GLFW_OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GLFW_OnMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void GLFW_OnMouseMove(GLFWwindow* window, double x, double y);
	static void GLFW_OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
	// Set vertical sync
	void SetVSync(bool enable);

private:
	// force to use the appropriate constructor
	Engine();
	
	// For internal use only. Used in Run()
	void privPreInitialize();
	void privPreLoadContent();

	// GLFW debug callback function
	static void APIENTRY Debug_Callback(GLenum source,
										GLenum type,
										GLuint id,
										GLenum severity,
										GLsizei length,
										const GLchar* message,
										GLvoid* userParam);
};

#endif


// ---  End of File ---------------
