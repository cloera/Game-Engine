//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef BLOCK_H
#define BLOCK_H

#include "Heap.h"

class Block
{
public:
	// defines for the heap name length
	static const unsigned int NameLength = 32;
	static const unsigned int NameNumChar = (Heap::NameLength - 1);

public:
	// Public methods
	Block *GetHeapNext();
	Block *GetHeapPrev();
	Block *GetGlobalNext();
	Block *GetGlobalPrev();
	char *GetFileName();
	int GetLineNum();
	int GetAllocIndex();
	unsigned int GetAllocSize();

protected:
	// Specialized Constructor
	Block(char * name, int lineNum, unsigned int allocSize, int allocIndex);

	// Setters
	void protSetHeapNext(Block *pBlock);
	void protSetHeapPrev(Block *pBlock);
	void protSetGlobalNext(Block *pBlock);
	void protSetGlobalPrev(Block *pBlock);

	// Helper functions
	void protPrintBlockInfo();

private:
	// Default constructor inaccessible. Use Specialized Constructor
	Block();

	// Total Size of this class:
	// 64 Bytes - add appropriate padding

	// Note: need to add Tracking Block links for Heap and Global lists
	//       Several ways to do it... I don't care
	//       No Templates

	// Total Size of this class:
	// 64 Bytes - add appropriate padding
	Block		   *pHeapNext;
	Block		   *pHeapPrev;
	Block		   *pGlobalNext;
	Block		   *pGlobalPrev;

   // Required
	char           mFileName[Block::NameLength];
	int            mLineNum;
	int            mAllocIndex;
	unsigned int   mAllocSize;

	Block          *pSecret;   // back pointer to the top of the trackingblock
};

#endif

// ---  End of File ---------------
