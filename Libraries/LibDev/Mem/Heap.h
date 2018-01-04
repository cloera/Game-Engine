//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef HEAP_H
#define HEAP_H

#include "HeapLink.h"

// Forward declaration
class Mem;
class Block;


// Heap class
class Heap : public HeapLink
{
public:
	// Constants 
	static const unsigned int NameLength = 32;
	static const unsigned int NameNumChar = (NameLength - 1);

	// Heap Types
	enum Type
	{
		Normal,
		Fixed,
		Dword = 0x7fffffff
	};

	// Info structure
	struct Info
	{
		char Name[Heap::NameLength];
		unsigned int StartAddr;
		unsigned int EndAddr;
		unsigned int TotalSize;
		int PeakNumAlloc;
		int CurrNumAlloc;
		int PeakBytesUsed;
		int CurrBytesUsed;
	};

public:
	// Public Interface (For Customers)
	void GetInfo(Info &info);

	// Tracking block 
	Block *GetTrackingHead();

	// Needed for Testings (Not for Customers)
	Heap *DebugGetNext() const;
	Heap *DebugGetPrev() const;


protected:
	// Specialized constructor
	Heap(Mem *pMem, HANDLE heapH, unsigned int heapSize, const char * const Name);

	// Allocate and free block on Win32 heap
	void* protAllocateBlock(size_t blockSize);
	void protFreeBlock(void *pBlock);

	// Destroy Win32 heap
	void protDestroyHeap();

	// Add and Remove tracking blocks from Heap list
	void protAddBlock(Block *pBlock);
	void protRemoveBlock(Block *pBlock);

	// Update stats for allocating block
	void protIncrementAllocInfo(unsigned int size);
	void protDecrementAllocInfo(unsigned int size);

private:
	// Default constructor inaccessible. Use specialized constructor
	Heap();

	// Helper methods
	void SetInfoName(const char * const Name);
	void privClearInfo();

	// data -----------------------------------------------------------------------
	Block		*pBlkHead;
	Type		mType;
	HANDLE		mWinHeapHandle;
	Info		mInfo;

	// Back link to the memory system
	Mem			*pMem;

};

#endif

// ---  End of File ---------------
