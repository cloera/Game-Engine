#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include "Model.h"

class PyramidModel : public Model
{
public:
	// Specialized constructor
	PyramidModel(const char* const modelFileName);

	// Big four constructors
	PyramidModel() = delete;
	PyramidModel(const PyramidModel &in) = delete;
	PyramidModel & operator=(const PyramidModel &in) = delete;
	~PyramidModel();

	// Delete vertex array object
	void DeleteVAO() override;
	// Delete vertex buffer object
	void DeleteVBO() override;

private:
	// Create vertex array object
	void privCreateVAOToFile(const char* const modelFileName) override;
	void privCreateVAOFromFile(const char* const modelFileName) override;

	// Create raw data
	void privCreatePyramid(Model::Vertice *&pData, Model::Tri_Index *&pTriList);
};
#endif // !PYRAMID_MODEL_H

