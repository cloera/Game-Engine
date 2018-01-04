#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include <sb7.h>
#include "PCSNode.h"

#include "TextureManager.h"


class Texture : public PCSNode
{
public:
	// Constructor
	Texture();

	// Setter
	void Set(const char* const ImageFileName, TextureManager::Name Name, GLuint TextureID,
			 GLenum MinFilter, GLenum MagFilter, GLenum WrapMode);

	// static data
	static const unsigned int TEXTURE_FILE_NAME_SIZE = 64;

private:
	// Private Data
	char imageFileName[Texture::TEXTURE_FILE_NAME_SIZE];

public:
	// Data
	TextureManager::Name texName;
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapMode;
};


#endif // !TEXTURE_NODE_H

