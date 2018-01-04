#ifndef HEAPSAP_H
#define HEAPSAP_H

#include "Heap.h"

// Forward Declaration
class Mem;
class Block;


/***************************************************
*  HeapSAP (Selection Application Pattern)
*  A Keenan original pattern.
*  Use this class to hide methods from customers.
*  Only to be used internally in Memory System.
****************************************************/
class HeapSAP : public Heap
{

public:
	// Specialized constructor
	HeapSAP(Mem *pMem, HANDLE heapH, unsigned int heapSize, const char * const Name);

	// Allocate and Free Block
	void* AllocateBlockInterface(size_t blockSize);
	void  FreeBlockInterface(void *pBlock);

	// Add and Remove Block
	Block* AddBlockInterface(void * pBlockAlloc, char * name, int lineNum, unsigned int allocSize, int allocIndex);
	void   RemoveBlockInterface(Block *pBlock);

	// Destroy Win32 heap
	void DestroyHeapInterface();

	void DecreAllocInfoInterface(unsigned int size);
};


#endif // !HEAPSAP_H

