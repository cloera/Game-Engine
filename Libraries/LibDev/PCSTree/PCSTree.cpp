//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "PCSTree.h"
#include "PCSNode.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"
#include "Trace.h"

#define STUB_PLEASE_REPLACE(x) (x)

// constructor
PCSTree::PCSTree()
{
	this->pRoot = nullptr;

	this->mInfo.currNumLevels = 0;
	this->mInfo.currNumNodes = 0;
	this->mInfo.maxNumLevels = 0;
	this->mInfo.maxNumNodes = 0;
};

// destructor
PCSTree::~PCSTree()
{
	this->mInfo.currNumLevels = 0;
	this->mInfo.currNumNodes = 0;
	this->mInfo.maxNumLevels = 0;
	this->mInfo.maxNumNodes = 0;
};


// get Root
PCSNode *PCSTree::GetRoot() const
{
	return this->pRoot;
}


// insert
void PCSTree::Insert(PCSNode * const pInNode, PCSNode * const pParent)
{
	assert(pInNode != nullptr);

	// if tree is empty
	if (pParent == nullptr && this->pRoot == nullptr)
	{
		// Set root to pInNode
		this->pRoot = pInNode;
		// Update info
		this->mInfo.currNumLevels = 1;
		// Check if max level needs to be updated
		this->privSetMaxLevels(pInNode);
	}
	// else something is in tree
	else
	{
		// if no children in parent, attach child
		if (pParent->GetChild() == nullptr)
		{
			// Set child to parent
			pParent->SetChild(pInNode);
			// Set parent to child
			pInNode->SetParent(pParent);

			// Max Levels may need to be updated since you're creating a new level
			this->privSetMaxLevels(pInNode);
		}
		// else add child node to parent and siblings
		else
		{
			// Save old child
			PCSNode *oldChild = pParent->GetChild();

			// Set parent to child
			pInNode->SetParent(pParent);

			// Attach child to front of sibling list
			// Set old child prevSibling to new child
			pParent->GetChild()->SetPrevSibling(pInNode);
			// Set new child nextSibling to old child
			pInNode->SetNextSibling(oldChild);

			// Set new child to parent
			pParent->SetChild(pInNode);
		}
	}

	// Update info
	this->mInfo.currNumNodes++;
	privSetMaxNodes();
}


// Remove
void PCSTree::Remove(PCSNode * const pInNode)
{
	assert(this->pRoot != nullptr);
	assert(pInNode != nullptr);

	// If child is null
	if (pInNode->GetChild() == nullptr)
	{
		// If pInNode does not have siblings
		if (pInNode->GetNextSibling() == nullptr && pInNode->GetPrevSibling() == nullptr)
		{
			// Are we at root?
			if (pInNode == this->pRoot)
			{
				// Yes, set root to null
				this->pRoot = nullptr;
			}
			else
			{
				// No, remove single child node
				privRemoveSingleChild(pInNode);
			}
		}
		// Else pInNode has siblings
		else
		{
			// Remove node from siblings
			privRemoveSibling(pInNode);
		}
		// Set pInNode pointers to null
		pInNode->ClearPointers();
		// Update mInfo
		this->mInfo.currNumNodes--;
	}
	// Else pInNode has children and/or siblings
	else
	{
		// Recurse on pInNode and its children
		// Remove all children of pInNode
		Remove(pInNode->GetChild());
		// Remove pInNode
		Remove(pInNode);
	}
}

void PCSTree::privRemoveSibling(PCSNode * const currNode)
{
	// Remove front sibling
	if (currNode->GetPrevSibling() == nullptr)
	{
		// Set child of parent to next sibling
		currNode->GetParent()->SetChild(currNode->GetNextSibling());
		// Set next sibling's prevSibling pointer to previous sibling
		currNode->GetNextSibling()->SetPrevSibling(currNode->GetPrevSibling());

	}
	// Remove last sibling
	else if (currNode->GetNextSibling() == nullptr)
	{
		// Set previous sibling's nextSibling pointer to next sibling
		currNode->GetPrevSibling()->SetNextSibling(currNode->GetNextSibling());
	}
	// Remove middle sibling
	else
	{
		// Set previous sibling's nextSibling pointer to next sibling
		currNode->GetPrevSibling()->SetNextSibling(currNode->GetNextSibling());
		// Set next sibling's prevSibling pointer to previous sibling
		currNode->GetNextSibling()->SetPrevSibling(currNode->GetPrevSibling());
	}
}

void PCSTree::privRemoveSingleChild(PCSNode * const currNode)
{
	// Set child of parent to null
	currNode->GetParent()->SetChild(currNode->GetChild());
	// Set parent of child to null
	currNode->SetParent(nullptr);
}

// get tree info
void PCSTree::GetInfo(Info &info)
{
	PCSNode *currNode = this->pRoot;
	// reset current number of levels
	this->mInfo.currNumLevels = 0;
	// if tree is not empty
	if (this->pRoot != nullptr)
	{
		// Calculate current levels here
		this->privCalcCurrLevels(currNode, 1);
	}
	// pass info to reference
	info = this->mInfo;
}

void PCSTree::Print() const
{
	Trace::out("\n\nPrint Tree --------------------------------------------\n");
	privPrintTree(this->pRoot, 0);
	Trace::out("-----------------------------------------------------------\n\n");
}

void PCSTree::privPrintTree(PCSNode * currNode, int levelCount) const
{
	bool isProcessing = true;

	while (isProcessing)
	{
		// Print current node
		privPrintLevelSeperator(levelCount);			// Print indentation
		Trace::out("Level(%i) :: ", levelCount + 1);	// Print level
		currNode->PrintNode();							// Print node

		// If child is not null
		if (currNode->GetChild() != nullptr)
		{
			// Traverse on child node and increment levelCount since we're going down level
			currNode = currNode->GetChild();
			levelCount += 1;
			continue;
		}
		
		// Traverse up tree until you get to a nextSibling or null parent
		while (currNode->GetNextSibling() == nullptr)
		{
			// If parent is null
			if (currNode->GetParent() == nullptr)
			{
				// Then at root node of tree. Stop processing
				isProcessing = false;
				break;
			}
			// Go to parent
			currNode = currNode->GetParent();
			// Decrement level count
			levelCount -= 1;
		}

		// Go to next sibling
		currNode = currNode->GetNextSibling();
	}
}

void PCSTree::privPrintLevelSeperator(int levelCount) const
{
	while (levelCount != 0)
	{
		Trace::out("\t");
		levelCount--;
	}
}


void PCSTree::privSetMaxNodes()
{
	if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes)
	{
		this->mInfo.maxNumNodes++;
	}
}
void PCSTree::privSetMaxLevels(PCSNode * const pInNode)
{
	int levelCount = 0;
	PCSNode *currNode = pInNode;

	// Go up tree until you hit the top
	while (currNode != nullptr)
	{
		// Increment level count
		levelCount++;
		// Move up to parent
		currNode = currNode->GetParent();
	}
	// If levelCount is greater than maxNumLevels
	if (levelCount > this->mInfo.maxNumLevels)
	{
		// Update maxNumLevels with new max level
		this->mInfo.maxNumLevels = levelCount;
	}
}


void PCSTree::privCalcCurrLevels(const PCSNode * currNode, int levelCount)
{
	bool isProcessing = true;

	while (isProcessing)
	{
		// If child is not null
		if (currNode->GetChild() != nullptr)
		{
			// Traverse on child node and increment levelCount since we're going down level
			currNode = currNode->GetChild();
			levelCount += 1;
			continue;
		}
		// If currNumLevels is less than levelCount
		if (this->mInfo.currNumLevels < levelCount)
		{
			// Update currNumLevels with new deepest level
			this->mInfo.currNumLevels = levelCount;
		}

		// Traverse up tree until you get to a nextSibling or null parent
		while (currNode->GetNextSibling() == nullptr)
		{
			// If parent is null
			if (currNode->GetParent() == nullptr)
			{
				// Then at root node of tree. Stop processing
				isProcessing = false;
				break;
			}

			// Go to parent
			currNode = currNode->GetParent();
			// Decrement level count
			levelCount -= 1;
		}

		// Go to next sibling
		currNode = currNode->GetNextSibling();
	}
}


// ---  End of File ---------------
