//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "PCSTree.h"
#include "PCSNode.h"
#include "Trace.h"

#define STUB_PLEASE_REPLACE(x) (x)

// constructor
PCSNode::PCSNode()
{
	this->ClearPointers();

	memset(&pName, 0x0, PCSNode::NAME_SIZE);
}

// copy constructor
PCSNode::PCSNode(const PCSNode &in)
{
	this->pParent = in.pParent;
	this->pChild = in.pChild;
	this->pNextSibling = in.pNextSibling;
	this->pPrevSibling = in.pPrevSibling;
	this->pForward = nullptr;
	this->pReverse = nullptr;

	memcpy_s(this->pName, sizeof(char)*PCSNode::NAME_SIZE, in.pName, sizeof(char)*PCSNode::NAME_SIZE);
}

// Specialize Constructor
PCSNode::PCSNode(PCSNode * const pInParent, PCSNode * const pInChild, PCSNode * const pInNextSibling, PCSNode * const pInPrevSibling, const char * const pInName)
{
	this->pParent = pInParent;
	this->pChild = pInChild;
	this->pNextSibling = pInNextSibling;
	this->pPrevSibling = pInPrevSibling;
	this->pForward = nullptr;
	this->pReverse = nullptr;

	memcpy_s(this->pName, sizeof(char)*PCSNode::NAME_SIZE, pInName, sizeof(char)*PCSNode::NAME_SIZE);
}

PCSNode::PCSNode(const char * const pInName)
{
	this->ClearPointers();

	memcpy_s(this->pName, sizeof(char)*PCSNode::NAME_SIZE, pInName, sizeof(char)*PCSNode::NAME_SIZE);
}

// destructor
PCSNode::~PCSNode()
{
	memset(&pName, 0x0, PCSNode::NAME_SIZE);
}

// assignment operator
PCSNode &PCSNode::operator = (const PCSNode &in)
{
	if (this != &in)
	{
		this->pChild = in.pChild;
		this->pParent = in.pParent;
		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;
		this->pForward = in.pForward;

		memcpy_s(this->pName, sizeof(char)*PCSNode::NAME_SIZE, in.pName, sizeof(char)*PCSNode::NAME_SIZE);
	}
	return *this;
}

void PCSNode::SetParent(PCSNode * const pIn)
{
	this->pParent = pIn;
}

void PCSNode::SetChild(PCSNode * const pIn)
{
	this->pChild = pIn;
}

void PCSNode::SetNextSibling(PCSNode * const pIn)
{
	this->pNextSibling = pIn;
}

void PCSNode::SetPrevSibling(PCSNode * const pIn)
{
	this->pPrevSibling = pIn;
}

void PCSNode::SetForward(PCSNode * const pIn)
{
	this->pForward = pIn;
}

void PCSNode::SetReverse(PCSNode * const pIn)
{
	this->pReverse = pIn;
}

PCSNode *PCSNode::GetParent(void) const
{
	return this->pParent;
}

PCSNode *PCSNode::GetChild(void) const
{
	return this->pChild;
}

PCSNode *PCSNode::GetNextSibling(void) const
{
	return this->pNextSibling;
}

PCSNode *PCSNode::GetPrevSibling(void) const
{
	return this->pPrevSibling;
}

PCSNode * PCSNode::GetForward(void) const
{
	return this->pForward;
}

PCSNode * PCSNode::GetReverse(void) const
{
	return this->pReverse;
}

void PCSNode::ClearPointers()
{
	this->pParent = nullptr;
	this->pChild = nullptr;
	this->pNextSibling = nullptr;
	this->pPrevSibling = nullptr;
	this->pForward = nullptr;
	this->pReverse = nullptr;
}

PCSNode::Code PCSNode::SetName(const char * const pInName)
{
	// Check for null pointers
	if (pInName == nullptr || this->pName == nullptr)
	{
		return Code::FAIL_NULL_PTR;
	}

	// Set destination buffer to null
	memset(this->pName, '\0', PCSNode::NAME_SIZE);
	// Copy whole pInName char buffer to pName
	memcpy_s(this->pName, sizeof(char) * (PCSNode::NAME_SIZE - 1), pInName, sizeof(char) * (PCSNode::NAME_SIZE - 1));
	return Code::SUCCESS;
}

PCSNode::Code PCSNode::GetName(char * const pOutBuffer, unsigned int sizeOutBuffer) const
{
	// Check for null pointers
	if (pOutBuffer == nullptr || this->pName == nullptr)
	{
		return Code::FAIL_NULL_PTR;
	}

	unsigned int srcSize = PCSNode::NAME_SIZE;
	// Check if sizeOutBuffer is smaller than source buffer size
	if (sizeOutBuffer < srcSize)
	{
		srcSize = sizeOutBuffer;
	}
	// Set destination buffer to null
	memset(pOutBuffer, '\0', sizeOutBuffer);
	// Copy whole pName buffer to pOutBuffer
	memcpy_s(pOutBuffer, sizeof(char) * (sizeOutBuffer - 1), this->pName, sizeof(char) * (srcSize - 1));
	return Code::SUCCESS;
}

void PCSNode::PrintNode() const
{
	Trace::out("PCSNode(0x%X) - pName: '%s', pParent: 0x%X, pChild: 0x%X, pNextSibling: 0x%X, pPrevSibling: 0x%X\n",
		this, this->pName, this->pParent, this->pChild, this->pNextSibling, this->pPrevSibling);
}

void PCSNode::PrintChildren() const
{
	// Print Current node
	Trace::out("Current :: ");
	this->PrintNode();

	// Print Child node
	Trace::out(" \tChild :: ");
	this->pChild->PrintNode();

	// Print Siblings
	this->pChild->PrintSiblings();
}


void PCSNode::PrintSiblings() const
{
	PCSNode *currNode = this->pNextSibling;

	// Iterate through all Siblings
	while (currNode != nullptr)
	{
		// Print Sibling node
		Trace::out(" \tSibling :: ");
		currNode->PrintNode();
		// Move to next Sibling node
		currNode = currNode->pNextSibling;
	}
}

int PCSNode::GetNumSiblings() const
{
	int numSiblings = 1;

	// Add count of all next siblings
	numSiblings += this->privGetNumNextSiblings();
	// Add count of all previous siblings
	numSiblings += this->privGetNumPrevSiblings();

	return numSiblings;
}

int PCSNode::privGetNumPrevSiblings() const
{
	PCSNode *currNode = this->pPrevSibling;
	int numSiblings = 0;

	while (currNode != nullptr)
	{
		// Increment Sibling counter
		numSiblings++;
		// Move to previous Sibling
		currNode = currNode->pPrevSibling;
	}
	return numSiblings;
}

int PCSNode::privGetNumNextSiblings() const
{
	PCSNode *currNode = this->pNextSibling;
	int numSiblings = 0;

	while (currNode != nullptr)
	{
		// Increment Sibling counter
		numSiblings++;
		// Move to Next Sibling
		currNode = currNode->pNextSibling;
	}
	return numSiblings;
}

int PCSNode::GetNumChildren() const
{
	int numChildren = 0;

	// If there is a child
	if (this->pChild != nullptr)
	{
		// Add up all siblings of child
		numChildren += this->pChild->GetNumSiblings();
	}
	return numChildren;
}

// ---  End of File ---------------
