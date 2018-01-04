#ifndef MODEL_H
#define MODEL_H

#include <sb7.h>
#include "MathEngine.h"

class Model
{
public:
	// Vertex layout
	struct Vertice
	{
		Vertice()
		{
			memset(this, 0x0, sizeof(Vertice));
		}

		void Set(float X, float Y, float Z, float U, float V, float Nx, float Ny, float Nz)
		{
			x = X; y = Y; z = Z;
			u = U; v = V;
			nx = Nx; ny = Ny; nz = Nz;
		}
		void SetNormal(float Nx, float Ny, float Nz)
		{
			nx = Nx; ny = Ny; nz = Nz;
		}
		Vect GetPos()
		{
			return Vect(x, y, z);
		}

		// Data
		float x, y, z;
		float u, v;
		float nx, ny, nz;
	};

	// Triangle index layout
	struct Tri_Index
	{
		Tri_Index()
		{
			memset(this, 0x0, sizeof(Tri_Index));
		}

		void Set(unsigned int V0, unsigned int V1, unsigned int V2)
		{
			v0 = V0; v1 = V1; v2 = V2;
		}

		// Data
		unsigned int v0, v1, v2;
	};

public:
	// Big Four constructors
	Model();
	Model(const Model &in) = delete;
	Model & operator=(const Model &in) = delete;
	virtual ~Model();

	// Delete vertex array/buffer object
	virtual void DeleteVAO() = 0;
	virtual void DeleteVBO() = 0;

	// Getters and Setters
	int GetNumVerts();
	int GetNumTris();
	GLuint GetVAO();

protected:
	void CreateModel(const char* const modelFileName);
	
	// Create vertex array object
	virtual void privCreateVAO(Model::Vertice *modelData, Model::Tri_Index *triList);
	virtual void privCreateVAOToFile(const char* const modelFileName) = 0;
	virtual void privCreateVAOFromFile(const char* const modelFileName) = 0;


	// Helper functions
	void WriteModelToFile(Vertice *modelData, Tri_Index *triList, const char * const modelName, const char * const modelFileName);
	void ReadModelFromFile(Vertice *&modelData, Tri_Index *&triList, const char* const modelFileName);
	bool CheckForModelFile(const char* const modelFileName);
	Vect CalcPolygonNormal(const Vect &vert1, const Vect &vert2, const Vect &vert3);


	// Data
	int	   numVerts;
	int	   numTris;
	GLuint VAO;
	GLuint VBO[2];
};

#endif // !MODEL_H

