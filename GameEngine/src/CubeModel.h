#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include "Model.h"

class CubeModel : public Model
{
public:
	// Specialized constructor
	CubeModel(const char* const modelFileName);

	// Big four constructors
	CubeModel() = delete;
	CubeModel(const CubeModel &in) = delete;
	CubeModel & operator=(const CubeModel &in) = delete;
	~CubeModel();

	// Delete vertex array object
	void DeleteVAO() override;
	// Delete vertex buffer object
	void DeleteVBO() override;

private:
	// Create vertex array object
	void privCreateVAOToFile(const char* const modelFileName) override;
	void privCreateVAOFromFile(const char* const modelFileName) override;

	void privCreateCube(Model::Vertice *&pData, Model::Tri_Index *&pTriList);
};

#endif // !CUBEMODEL_H

