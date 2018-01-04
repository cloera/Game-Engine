#ifndef DIAMOND_MODEL_H
#define DIAMOND_MODEL_H


#include "Model.h"

class DiamondModel : public Model
{
public:
	// Specialized constructor
	DiamondModel(const char* const modelFileName);

	// Big four constructors
	DiamondModel() = delete;
	DiamondModel(const DiamondModel &in) = delete;
	DiamondModel & operator=(const DiamondModel &in) = delete;
	~DiamondModel();

	// Delete vertex array object
	void DeleteVAO() override;
	// Delete vertex buffer object
	void DeleteVBO() override;

private:
	// Create vertex array object
	void privCreateVAOToFile(const char* const modelFileName) override;
	void privCreateVAOFromFile(const char* const modelFileName) override;

	// Create raw data
	void privCreateDiamond(Model::Vertice *&pData, Model::Tri_Index *&pTriList);
};

#endif // !DIAMOND_MODEL

