#ifndef PCSTREE_FORWARD_ITERATOR_H
#define PCSTREE_FORWARD_ITERATOR_H

#include "PCSTreeIterator.h"

class PCSTreeForwardIterator : public PCSTreeIterator
{
public:
	// copy constructor
	PCSTreeForwardIterator(const PCSTreeForwardIterator &in);
	// assignment operator
	PCSTreeForwardIterator operator=(const PCSTreeForwardIterator &in);
	// specialized constructor
	PCSTreeForwardIterator(PCSNode *rootNode);

	// iterator methods
	virtual PCSNode *First() override;
	virtual PCSNode *Next() override;
	virtual bool IsDone() override;
	virtual PCSNode *CurrentItem() override;

private:
	// Don't use default constructor
	PCSTreeForwardIterator();
	// Create iterator from given rootNode
	void privCreateForward(PCSNode *rootNode);

	// data
	// vTable *vPtr;  virtual table pointer
	PCSNode *root;
	PCSNode *current;
};


#endif;