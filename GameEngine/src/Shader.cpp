#include <assert.h>
#include "Trace.h"

#include "Shader.h"
#include "File.h"

Shader::Shader(const char * const baseShaderFileName, Shader::Name shaderName)
{
	// Set shader name
	this->shaderName = shaderName;

	// Creates an empty program object and returns a non-zero value by which it can be referenced. 
	// A program object is an object to which shader objects can be attached. 
	this->program = glCreateProgram();
	
	// Create shader and attach to program
	privCreateShader(this->program, baseShaderFileName);
}

Shader::~Shader()
{
}

void Shader::SetActiveProgram()
{
	glUseProgram(this->program);
}

GLint Shader::GetUniformLocation(const char * const name)
{
	// name must not be null
	assert(name != 0);

	// Get location of uniform variable
	GLint location = glGetUniformLocation(this->program, name);
	assert(location != -1);

	return location;
}

Shader::Name Shader::GetShaderName()
{
	return this->shaderName;
}

void Shader::DeleteProgram()
{
	glDeleteProgram(this->program);
}

void Shader::privCreateShader(GLuint programObject, const char * const baseShaderFileName)
{
	char shaderFileName[128];

	// Get full vertex shader file name
	strcpy_s(shaderFileName, baseShaderFileName);
	strcat_s(shaderFileName, "_VS.glsl");
	// Load vertex shader file
	GLuint vertexObject = privLoadShaderFile(shaderFileName, GL_VERTEX_SHADER);
	assert(&vertexObject != 0);

	// Clear buffer
	memset(shaderFileName, 0x0, 128);

	// Get full fragment shader file name
	strcpy_s(shaderFileName, baseShaderFileName);
	strcat_s(shaderFileName, "_FS.glsl");
	// Load fragment shader file
	GLuint fragmentObject = privLoadShaderFile(shaderFileName, GL_FRAGMENT_SHADER);
	assert(&fragmentObject != 0);

	// glAttachShader — Attaches a shader object to a program object
	glAttachShader(programObject, vertexObject);
	glAttachShader(programObject, fragmentObject);

	// glLinkProgram — Links a program object
	glLinkProgram(programObject);
}

GLuint Shader::privLoadShaderFile(const char * const fileName, GLenum shaderType)
{
	File::Handle fh;
	File::Error  ferror;
	unsigned int fileSize;

	// Open shader file for READ
	ferror = File::Open(fh, fileName, File::READ);
	assert(ferror == File::Error::SUCCESS);

	// Seek to end of file
	ferror = File::Seek(fh, File::Location::END, 0);
	assert(ferror == File::Error::SUCCESS);

	// Get size of entire file
	ferror = File::Tell(fh, fileSize);
	assert(ferror == File::Error::SUCCESS);

	// Seek to beginning of file
	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	// Initialize shaderData
	char *shaderData = new char[fileSize + 1];
	assert(shaderData != 0);

	// Read file
	ferror = File::Read(fh, shaderData, fileSize);
	assert(ferror == File::Error::SUCCESS);

	// Add null terminator to end of shaderData
	shaderData[fileSize] = 0;

	// Close file
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	// Compile shader file
	GLuint shaderObject;
	bool status = privCompileShader(shaderObject, shaderData, shaderType, fileName);
	assert(status == true);

	// delete shader data buffer
	delete shaderData;

	// If status is false
	if (!status)
	{
		// return no data
		return 0;
	}

	return shaderObject;
}

bool Shader::privCompileShader(GLuint &outShaderObject, char *shaderData, GLenum shaderType, const char* const fileName)
{
	// glCreateShader creates an empty shader object and returns a non-zero value by which it can be referenced. 
	// A shader object is used to maintain the source code strings that define a shader. 
	// shaderType indicates the type of shader to be created.
	outShaderObject = glCreateShader(shaderType);
	assert(outShaderObject != 0);

	// glShaderSource — Replaces the source code in a shader object
	glShaderSource(outShaderObject, 1, &shaderData, 0);

	// glCompileShader — Compiles a shader object
	glCompileShader(outShaderObject);

	// Did shader compile correctly?
	GLint status = 0;
	glGetShaderiv(outShaderObject, GL_COMPILE_STATUS, &status);

	// If status has errors
	if (!status)
	{
		// Get information log about shader
		char logInfo[4096];
		glGetShaderInfoLog(outShaderObject, 4096, NULL, logInfo);

		printf("Error(Shader::privCompileShader) %s: %s\n", fileName, shaderData);

		// Delete shader object
		glDeleteShader(outShaderObject);

		return false;
	}

	return true;
}
