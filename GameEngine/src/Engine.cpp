#include "Engine.h"

Engine * Engine::pApp = 0;


Engine::Engine(const char* windowName, const int Width, const int Height)
{
	strcpy_s(info.title,128, windowName);
	info.windowWidth = Width;
	info.windowHeight = Height;

	info.majorVersion = 4;
	info.minorVersion = 3;

	info.samples = 0;
	info.flags.all = 0;
	info.flags.cursor = 1;

#ifdef _DEBUG
	info.flags.debug = 1;
#endif

}

Engine::Engine()
{
	strcpy_s(info.title, 128, "DEFAULT SETUP please redo");
	info.windowWidth = 800;
	info.windowHeight = 600;

	info.majorVersion = 4;
	info.minorVersion = 3;

	info.samples = 0;
	info.flags.all = 0;
	info.flags.cursor = 1;

#ifdef _DEBUG
	info.flags.debug = 1;
#endif

}

Engine::~Engine() 
{
}

//------------------------------------------------------------------
// Engine::Run()
//		This is the internal game loop that the engine runs on.
//------------------------------------------------------------------
void Engine::Run()
{
	// Initialize Engine and glfw
	this->privPreInitialize();
	
	// Derived class' initializations
	Initialize(); // virtual

	// Load window settings through glfw
	this->privPreLoadContent();

	// ATI cards have a problem with page flipping
	// This forces the card to honor vertical sync
	SetVSync(true);

	// Derived class' content loading
	LoadContent(); // virtual

	// Render to window until ESC key is pressed or window is closed
	while ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) && (glfwWindowShouldClose(window) != GL_TRUE))
	{
		// move objects
		Update( (float)glfwGetTime() );

		// clear screen
		ClearBuffer();

		// render objects
		Render();  // Virtual

		// Swap the back and front buffers of the window
		glfwSwapBuffers(window);
		// GLFW 3 function that processes events in queue.
		// Calls window and input callbacks associated with event
		glfwPollEvents();

	}

	// Derived class' content unloading
	UnLoadContent(); // virtual

	// Destroy glfw window
	glfwDestroyWindow(window);
	// Terminate glfw
	glfwTerminate();
}

void Engine::privPreInitialize()
{
	// Set pApp
	pApp = this;

	// If glfw cannot initialize
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}
}

void Engine::privPreLoadContent()
{
	// Set major and minor of minimum opengl version that can be used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);

#ifndef _DEBUG
	if (info.flags.debug)
	{
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}
#endif /* _DEBUG */
	if (info.flags.robust)
	{
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
	}
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, info.samples);
	glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);
	
	// Create window
	window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title, info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	// If not window was not created
	if (!window)
	{
		fprintf(stderr, "Failed to open window\n");
		return;
	}

	// Make the OpenGL context of the specified window current on the calling thread
	glfwMakeContextCurrent(window);

	// Set functions callbacks for window, mouse, and keyboard
	glfwSetWindowSizeCallback(window, GLFW_OnResize);
	glfwSetKeyCallback(window, GLFW_OnKey);
	glfwSetMouseButtonCallback(window, GLFW_OnMouseButton);
	glfwSetCursorPosCallback(window, GLFW_OnMouseMove);
	glfwSetScrollCallback(window, GLFW_OnMouseWheel);
	// Is cursor flag set to false?
	if (!info.flags.cursor)
	{
		// Hide mouse cursor. Cursor will not be confined to window
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	// Initialize gl3w
	gl3wInit();

#ifdef _DEBUG
	fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
	fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
	fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif

	if (info.flags.debug)
	{
		// check if gl3w 4.3 is supported
		if (gl3wIsSupported(4, 3))
		{
			glDebugMessageCallback((GLDEBUGPROC)Debug_Callback, this);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		}
		// check if OpenGL ARB extension is supported
		else if (sb6IsExtensionSupported("GL_ARB_debug_output"))
		{
			glDebugMessageCallbackARB((GLDEBUGPROC)Debug_Callback, this);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		}
	}

	// Set culling and depth
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Engine::Initialize()
{
	strcpy_s(info.title, 128, "OpenGL SuperBible Example");
	info.windowWidth = 800;
	info.windowHeight = 600;
#ifdef __APPLE__
	info.majorVersion = 3;
	info.minorVersion = 2;
#else
	info.majorVersion = 4;
	info.minorVersion = 3;
#endif
	info.samples = 0;
	info.flags.all = 0;
	info.flags.cursor = 1;
#ifdef _DEBUG
	info.flags.debug = 1;
#endif
}

void Engine::LoadContent()
{
}

void Engine::Render()
{

}

void Engine::UnLoadContent()
{
}

//------------------------------------------------------------------
// Engine::ClearBuffer()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Engine::ClearBuffer()
{
	const GLfloat grey[] = { 0.250f, 0.25f, 0.25f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void APIENTRY Engine::Debug_Callback(GLenum source,
											   GLenum type,
											   GLuint id,
											   GLenum severity,
											   GLsizei length,
											   const GLchar* message,
											   GLvoid* userParam)
{
	reinterpret_cast<Engine *>(userParam)->OnDebugMessage(source, type, id, severity, length, message);
}

int Engine::GetKey(int key)
{
	return glfwGetKey(this->window, key);
}

int Engine::GetMouseButton(int key)
{
	return glfwGetMouseButton(this->window, key);
}

void Engine::SetWindowTitle(const char * title)
{
	glfwSetWindowTitle(window, title);
}

void Engine::OnResize(int w, int h)
{
	info.windowWidth = w;
	info.windowHeight = h;
}

void Engine::OnKey(int key, int action)
{
	UNUSED_VAR(key);
	UNUSED_VAR(action);
}

void Engine::OnMouseButton(int button, int action)
{
	UNUSED_VAR(button);
	UNUSED_VAR(action);
}

void Engine::OnMouseMove(int x, int y)
{
	UNUSED_VAR(x);
	UNUSED_VAR(y);
}

void Engine::OnMouseWheel(int pos)
{
	UNUSED_VAR(pos);
}

void Engine::OnDebugMessage(GLenum source,
							GLenum type,
							GLuint id,
							GLenum severity,
							GLsizei length,
							const GLchar* message)
{
	UNUSED_VAR(length);
	UNUSED_VAR(severity);
	UNUSED_VAR(id);
	UNUSED_VAR(type);
	UNUSED_VAR(source);

#ifdef _WIN32
	OutputDebugStringA(message);
	OutputDebugStringA("\n");
#endif /* _WIN32 */
}

void Engine::GetMousePosition(int& x, int& y)
{
	double dx, dy;
	glfwGetCursorPos(window, &dx, &dy);

	x = static_cast<int>(floor(dx));
	y = static_cast<int>(floor(dy));
}

void Engine::GetMousePosition(float & x, float & y)
{
	double dx, dy;
	glfwGetCursorPos(window, &dx, &dy);

	x = (float)dx;
	y = (float)dy;
}

void Engine::GLFW_OnResize(GLFWwindow* window, int w, int h)
{
	UNUSED_VAR(window);

	pApp->OnResize(w, h);
}

void Engine::GLFW_OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	UNUSED_VAR(mods);
	UNUSED_VAR(scancode);
	UNUSED_VAR(window);

	pApp->OnKey(key, action);
}

void Engine::GLFW_OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	UNUSED_VAR(mods);
	UNUSED_VAR(window);

	pApp->OnMouseButton(button, action);
}

void Engine::GLFW_OnMouseMove(GLFWwindow* window, double x, double y)
{
	UNUSED_VAR(window);

	pApp->OnMouseMove(static_cast<int>(x), static_cast<int>(y));
}

void Engine::GLFW_OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	UNUSED_VAR(window);
	UNUSED_VAR(xoffset);

	pApp->OnMouseWheel(static_cast<int>(yoffset));
}

void Engine::SetVSync(bool enable)
{
	info.flags.vsync = enable ? 1u : 0u;
	glfwSwapInterval((int)info.flags.vsync);

}


// ---  End of File ---------------
