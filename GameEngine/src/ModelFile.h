#ifndef MODEL_FILE_H
#define MODEL_FILE_H

#define MODEL_NAME_SIZE 32
#define TEXTURE_NAME_SIZE 32

class ModelFile
{
public:
	ModelFile()
	{
		// Zero out whole class
		memset(this, 0x0, sizeof(ModelFile));
	};

	/** Model File Header Data **/

	// Model name
	char modelName[MODEL_NAME_SIZE];

	// Vertex buffer
	int			 numVerts;
	unsigned int vertBufferOffset;

	// Triangle list index
	int			 numTriList;
	unsigned int triListBufferOffset;

	// Texture info
	//char         textName[TEXTURE_NAME_SIZE];
	//unsigned int textMinFilter;
	//unsigned int textMagFilter;
	//unsigned int textWrapMode;
};
#endif // !MODEL_FILE_H

