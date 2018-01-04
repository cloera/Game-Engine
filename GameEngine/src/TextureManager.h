#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <sb7.h>
#include "PCSTree.h"

class Texture;

// Singleton
class TextureManager
{
public:
	// Texture name enum
	enum class Name
	{
		STONES,
		RED_BRICK,
		DUCKWEED,
		ROCKS,
		NOT_INITIALIZED
	};

	static void AddTexture(const char* const ImageFileName, const Name Name);
	static void DeleteTextures();
	static GLuint Find(const Name Name);

private:
	// Hide constructor so no one can initialize TextureManager
	TextureManager();
	// Get singleton instance of TextureManager
	static TextureManager* privGetInstance();

	// Helper Methods
	void privLoadTexture(const char * const ImageFileName, GLuint *&TextureID);
	bool privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint wrapMode);
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	// Data
	PCSTree *pTree;
};


#endif // !TEXTURE_MANAGER_H

