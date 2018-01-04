
#include "HeapSAP.h"
#include "BlockSAP.h"


HeapSAP::HeapSAP(Mem * pMem, HANDLE heapH, unsigned int heapSize, const char * const Name)
	: Heap(pMem, heapH, heapSize, Name)
{
}

void * HeapSAP::AllocateBlockInterface(size_t blockSize)
{
	// Allocate space on Win32 heap while taking Block size and padding into account
	return (void *)this->protAllocateBlock(blockSize);
}

void HeapSAP::FreeBlockInterface(void * pBlock)
{
	this->protFreeBlock(pBlock);
}

Block * HeapSAP::AddBlockInterface(void * pBlockAlloc, char * name, int lineNum, unsigned int allocSize, int allocIndex)
{
	// placement new on tracking block
	Block *pBlock = (Block *) new(pBlockAlloc) BlockSAP(name, lineNum, allocSize, allocIndex);

	// attach tracking block to heap list
	this->protAddBlock(pBlock);

	// update stats
	this->protIncrementAllocInfo(allocSize);

	return pBlock;
}

void HeapSAP::RemoveBlockInterface(Block * pBlock)
{
	this->protRemoveBlock(pBlock);
}

void HeapSAP::DestroyHeapInterface()
{
	this->protDestroyHeap();
}

void HeapSAP::DecreAllocInfoInterface(unsigned int size)
{
	this->protDecrementAllocInfo(size);
}
