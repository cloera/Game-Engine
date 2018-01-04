#ifndef SHADER_H
#define SHADER_H

#include <sb7.h>

class Shader
{
public:
	// Shader name enum
	enum Name
	{
		COLOR_SIMPLE,
		COLOR_POSITION,
		COLOR_LIGHT,
		TEXTURE_FLAT,
		TEXTURE_LIGHT,
		NULL_SHADER
	};

	// Specialized constructor
	Shader(const char* const baseShaderFileName, Shader::Name shaderName);
	// Destructor
	~Shader();

	// Sets program object as part of current rendering state
	void SetActiveProgram();
	// Gets location of uniform variable in shader
	GLint GetUniformLocation(const char* const locationName);

	// Getters for member variables
	Shader::Name GetShaderName();

	// Delete program
	void DeleteProgram();

private:
	// This should not be called
	Shader();
	
	// Create shader object
	void privCreateShader(GLuint programObject, const char* const baseShaderFileName);
	// Load shader object
	GLuint privLoadShaderFile(const char * const fileName, GLenum shaderType);
	// Compile shader object
	bool privCompileShader(GLuint &outShaderObject, char *shaderData, GLenum shaderType, const char* const fileName);

	// Data
	Name shaderName;
	GLuint program;
};


#endif // !SHADER_H

