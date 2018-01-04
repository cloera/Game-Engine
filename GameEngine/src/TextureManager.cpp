#include <sb7.h>
#include <stdlib.h>
#include <assert.h>

#include "File.h"
#include "PCSTree.h"
#include "PCSTreeForwardIterator.h"

#include "TGA.h"
#include "Texture.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
	// Initialize PCSTree
	this->pTree = new PCSTree();
	assert(this->pTree != 0);
}

TextureManager * TextureManager::privGetInstance()
{
	// Instance of TextureManager is stored in BSS segment (https://en.wikipedia.org/wiki/Data_segment#BSS)
	static TextureManager instance;
	return &instance;
}

void TextureManager::AddTexture(const char * const ImageFileName, const TextureManager::Name Name)
{
	GLuint textureID;
	GLuint *pTextureID = &textureID;

	// Get instance of manager
	TextureManager *pInstance = TextureManager::privGetInstance();

	// Load texture and get textureID
	pInstance->privLoadTexture(ImageFileName, pTextureID);

	// Create TextureNode
	Texture *pNode = new Texture();

	// Set node data
	pNode->Set(ImageFileName, Name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	// Add node to manager
	pInstance->pTree->Insert(pNode, pInstance->pTree->GetRoot());
}

void TextureManager::DeleteTextures()
{
	// Get instance of manager
	TextureManager *pInstance = TextureManager::privGetInstance();
	// Get forward iterator from tree root node
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	// Get first node
	PCSNode *pNode = iter.First();
	
	// Delete all the textures... All of them!
	Texture *pTexture;
	while (!iter.IsDone())
	{
		// Is pNode still valid?
		assert(pNode != 0);
		// Get texture
		pTexture = (Texture *)pNode;
		// Delete texture in GPU
		glDeleteTextures(1, &pTexture->textureID);

		// Move to next node
		pNode = iter.Next();
	}

	// Delete Texture root and all of its children
	pInstance->pTree->Remove(pInstance->pTree->GetRoot());
}

GLuint TextureManager::Find(const TextureManager::Name Name)
{
	// Get instance of manager
	TextureManager *pInstance = TextureManager::privGetInstance();
	// Get forward iterator from tree root node
	PCSTreeForwardIterator iter(pInstance->pTree->GetRoot());
	// Get first node
	PCSNode *pNode = iter.First();

	// Delete all the textures... All of them!
	Texture *pTexture = 0;
	while (!iter.IsDone())
	{
		// Is pNode still valid?
		assert(pNode != 0);
		// Get texture
		pTexture = (Texture *)pNode;
		
		// If the Texture names match
		if (pTexture->texName == Name)
		{
			// Found it. Now break loop
			break;
		}

		// Move to next node
		pNode = iter.Next();
	}

	return pTexture->textureID;
}


void TextureManager::privLoadTexture(const char * const ImageFileName, GLuint *& TextureID)
{
	// Get ID just for textures - OpenGL poor man's handle
	glGenTextures(1, TextureID);

	// Bind ID handle
	glBindTexture(GL_TEXTURE_2D, *TextureID);

	// Load actual texture
	this->privLoadTGATexture(ImageFileName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

bool TextureManager::privLoadTGATexture(const char * szFileName, GLint minFilter, GLint magFilter, GLint wrapMode)
{
	GLbyte *pBits;
	GLenum eFormat;
	int nWidth;
	int nHeight;
	int nComponents;

	// Read bits from the texture
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == 0)
	{
		return false;
	}

	// Settings for U,V positions of texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrapMode);

	// Settings for texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

	// Define texture data and send it to the GPU
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	// Delete bits since they are stored in GPU now
	free(pBits);

	// Create mipmap of texture if requested
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return true;
}


////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte * TextureManager::gltReadTGABits(const char * szFileName, GLint * iWidth, GLint * iHeight, GLint * iComponents, GLenum * eFormat)
{
	File::Handle fh;		  // File handle
	File::Error  ferror;	  // File error handle
	TGAHEADER tgaHeader;	  // TGA file header
	unsigned long lImageSize; // Size in bytes of image
	short sDepth;			  // Pixel depth;
	GLbyte	*pBits = NULL;    // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Try to open file
	ferror = File::Open(fh, szFileName, File::Mode::READ);
	// If open failed
	if (ferror == File::Error::OPEN_FAIL)
		return NULL; // abort

	// Read TGA header (binary)
	ferror = File::Read(fh, &tgaHeader, 18 /*sizeof(TGAHEADER)*/);
	assert(ferror == File::Error::SUCCESS);

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL; // abort

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width *  (unsigned int)tgaHeader.height *  (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Make sure file handle is pointing to file data and not file header
	ferror = File::Seek(fh, File::Location::BEGIN, 18 /*sizeof(TGAHEADER)*/);
	assert(ferror == File::Error::SUCCESS);

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	ferror = File::Read(fh, pBits, lImageSize);
	if (ferror == File::Error::READ_FAIL)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	// Most likely case
	case 3:     
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;
	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	// Not concerned with this case
	case 1:
		assert(false);
		//  *eFormat = GL_LUMINANCE;
		//  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
		break;		// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!
	}

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	return pBits;
}
