#include <assert.h>
#include "PCSTreeForwardIterator.h"


#define STUB_PLEASE_REPLACE(x) (x)

PCSTreeForwardIterator::PCSTreeForwardIterator()
{
	this->root = nullptr;
	this->current = nullptr;
}

PCSTreeForwardIterator::PCSTreeForwardIterator(const PCSTreeForwardIterator & in)
{
	this->root = in.root;
	this->current = in.current;
}

PCSTreeForwardIterator PCSTreeForwardIterator::operator=(const PCSTreeForwardIterator & in)
{
	if (this != &in)
	{
		this->root = in.root;
		this->current = in.current;
	}
	return *this;
}

PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode *rootNode)
{
	this->root = rootNode;
	this->current = rootNode;

	// Create Forward iterator
	privCreateForward(rootNode);
}

PCSNode *PCSTreeForwardIterator::First()
{
	return this->root;
}

PCSNode *PCSTreeForwardIterator::Next()
{
	this->current = this->current->GetForward();
	return this->current;
}


bool PCSTreeForwardIterator::IsDone()
{
	// if current is nullptr then we are done else not done
	return this->current == nullptr;
}

PCSNode *PCSTreeForwardIterator::CurrentItem()
{
	return this->current;
}

void PCSTreeForwardIterator::privCreateForward(PCSNode *rootNode)
{
	PCSNode *parentNode = nullptr;
	PCSNode *currNode = rootNode;

	// While currNode is not null, start setting foward for tree.
	while (currNode != nullptr)
	{
		// If child is not null
		if (currNode->GetChild() != nullptr)
		{
			// Set forward
			currNode->SetForward(currNode->GetChild());
			// Traverse on child node
			currNode = currNode->GetChild();
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
			// Then set Forward to sibling of parent node
			currNode->SetForward(parentNode->GetNextSibling());
			// Go to sibling node of parent
			currNode = parentNode->GetNextSibling();
		}
		// else parentNode is root
		else 
		{
			// if child of parentNode is null
			if (parentNode->GetChild() == nullptr)
			{
				// Set Forward to null
				currNode->SetForward(nullptr);
			}
			// No more nodes to traverse
			currNode = nullptr;
		}
	}
}

