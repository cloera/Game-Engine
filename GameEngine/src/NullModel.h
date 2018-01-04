#ifndef NULL_MODEL_H
#define NULL_MODEL_H

#include "Model.h"

class NullModel : public Model
{
public:
	// Constructor
	NullModel();
	// Delete these to prevent copying and use
	NullModel(const NullModel &in) = delete;
	NullModel & operator=(const NullModel &in) = delete;
	// Destructor
	~NullModel();

	// Delete vertex array object
	void DeleteVAO() override;
	// Delete vertex buffer object
	void DeleteVBO() override;

private:
	// Create vertex array object
	void privCreateVAO(Model::Vertice *modelData, Model::Tri_Index *triList) override;
	void privCreateVAOToFile(const char* const modelFileName) override;
	void privCreateVAOFromFile(const char* const modelFileName) override;
};


#endif // !NULL_MODEL_H

