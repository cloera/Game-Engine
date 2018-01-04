#ifndef PCSTREE_REVERSE_ITERATOR_H
#define PCSTREE_REVERSE_ITERATOR_H

#include "PCSTreeIterator.h"

class PCSTreeReverseIterator : public PCSTreeIterator
{
public:
	// copy constructor
	PCSTreeReverseIterator(const PCSTreeReverseIterator &in);
	// assignment operator
	PCSTreeReverseIterator operator=(const PCSTreeReverseIterator &in);
	// specialized constructor
	PCSTreeReverseIterator(PCSNode *rootNode);

	virtual PCSNode *First() override;
	virtual PCSNode *Next() override;
	virtual bool IsDone() override;
	virtual PCSNode *CurrentItem() override;

private:
	// Don't use default constructor
	PCSTreeReverseIterator();
	// Create iterator from given rootNode
	void privCreateReverse(PCSNode *rootNode);

	PCSNode *root;
	PCSNode *current;
	PCSNode *prevNode;
};


#endif;