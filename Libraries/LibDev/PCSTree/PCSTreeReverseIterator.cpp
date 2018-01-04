#include <assert.h>
#include "PCSTreeReverseIterator.h"


#define STUB_PLEASE_REPLACE(x) (x)

PCSTreeReverseIterator::PCSTreeReverseIterator()
{
	this->root = nullptr;
	this->current = nullptr;
	this->prevNode = nullptr;
}

PCSTreeReverseIterator::PCSTreeReverseIterator(const PCSTreeReverseIterator & in)
{
	this->root = in.root;
	this->current = in.current;
	this->prevNode = in.prevNode;
}

PCSTreeReverseIterator PCSTreeReverseIterator::operator=(const PCSTreeReverseIterator & in)
{
	if (this != &in)
	{
		this->root = in.root;
		this->current = in.current;
		this->prevNode = in.prevNode;
	}
	return *this;
}

PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode *rootNode)
{
	this->root = rootNode;
	this->prevNode = rootNode;

	// Create reverse iterator
	privCreateReverse(this->prevNode);

	// Set current to prevNode to start at end of iterator
	this->current = this->prevNode;
}

PCSNode *PCSTreeReverseIterator::First()
{
	return this->prevNode;
}

PCSNode *PCSTreeReverseIterator::Next()
{
	this->current = this->current->GetReverse();
	return this->current;
}

bool PCSTreeReverseIterator::IsDone()
{
	return this->current == nullptr;
}

PCSNode *PCSTreeReverseIterator::CurrentItem()
{
	return this->current;
}

void PCSTreeReverseIterator::privCreateReverse(PCSNode * rootNode)
{
	PCSNode *parentNode = nullptr;
	PCSNode *currNode = rootNode;

	// While currNode is not null, traverse tree forward and set reverse for nodes.
	while (currNode != nullptr)
	{
		// If child is not null
		if (currNode->GetChild() != nullptr)
		{
			// Traverse on child node
			currNode = currNode->GetChild();
			// Set currNode reverse to prevNode
			currNode->SetReverse(this->prevNode);
			// Set prevNode to current node
			this->prevNode = currNode;
			continue;
		}

		parentNode = currNode;

		// Traverse up tree until you get to a nextSibling or parentNode is at root
		while (parentNode->GetNextSibling() == nullptr && parentNode != this->root)
		{
			// Go to parent
			parentNode = parentNode->GetParent();
		}

		// If parentNode is not root
		if (parentNode != this->root)
		{
			// Go to sibling node of parent
			currNode = parentNode->GetNextSibling();
			// Set currNode reverse to prevNode
			currNode->SetReverse(this->prevNode);
			// Set prevNode to currNode
			this->prevNode = currNode;
		}
		// else parentNode is root
		else
		{
			// if child of parentNode is null
			if (parentNode->GetChild() == nullptr)
			{
				// Set reverse to null
				parentNode->SetReverse(nullptr);
			}
			// Set parentNode(root) reverse to null since it is end of iterator
			parentNode->SetReverse(nullptr);
			// No more nodes to traverse
			currNode = nullptr;
		}
	}
}
