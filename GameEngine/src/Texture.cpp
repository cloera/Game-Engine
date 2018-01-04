#include "Texture.h"

Texture::Texture()
	: texName(TextureManager::Name::NOT_INITIALIZED), textureID(0),
	minFilter(GL_LINEAR), magFilter(GL_LINEAR), wrapMode(GL_CLAMP_TO_EDGE)
{
	memset(this->imageFileName, 0x0, TEXTURE_FILE_NAME_SIZE);
}

void Texture::Set(const char * const ImageFileName, TextureManager::Name Name, GLuint TextureID,
					  GLenum MinFilter, GLenum MagFilter, GLenum WrapMode)
{
	memcpy_s(this->imageFileName, TEXTURE_FILE_NAME_SIZE - 1, ImageFileName, TEXTURE_FILE_NAME_SIZE - 1);
	this->texName = Name;
	this->textureID = TextureID;
	this->magFilter = MagFilter;
	this->minFilter = MinFilter;
	this->wrapMode = WrapMode;
}

