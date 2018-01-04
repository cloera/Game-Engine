//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_H
#define PCSTREE_H


// forward declare
class PCSNode;
class PCSTreeForwardIterator;
class PCSTreeReverseIterator;

// PCSTree class 
class PCSTree
{
public:
	// Simple data structure
	struct Info
	{
		int currNumNodes;
		int maxNumNodes;
		int currNumLevels;
		int maxNumLevels;
	};

public:
	// constructor
	PCSTree();

	// copy constructor 
	PCSTree(const PCSTree &in) = delete;

	// assignment operator
	PCSTree & operator = (const PCSTree &in) = delete;

	// destructor
	~PCSTree();

	// get Root
	PCSNode *GetRoot() const;

	// insert
	void Insert(PCSNode * const pInNode, PCSNode * const pParent);

	// remove
	void Remove(PCSNode * const pInNode);

	// get info
	void GetInfo(Info &info);
	void Print() const;

private:
	// GetInfo helper functions
	void privSetMaxNodes();
	void privSetMaxLevels(PCSNode * const pInNode);
	void privCalcCurrLevels(const PCSNode * currNode, int levelCount);

	// Remove helper functions
	void privRemoveSibling(PCSNode * const currNode);
	void privRemoveSingleChild(PCSNode * const currNode);

	// Print helper function
	void privPrintTree(PCSNode * currNode, int levelCount) const;
	void privPrintLevelSeperator(int levelCount) const;

	// Data
	Info	mInfo;
	PCSNode *pRoot;

};

#endif

// ---  End of File ---------------
