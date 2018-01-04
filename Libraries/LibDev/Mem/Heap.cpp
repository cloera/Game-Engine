//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <assert.h>
#include <new.h>  // for placement new

#include "Heap.h"
#include "BlockSAP.h"

#include "Win32Wrapper.h"

#define STUB_PLEASE_REPLACE(x) (x)

Heap::Heap()
{
	this->pBlkHead = nullptr;
	this->mType = Heap::Type::Normal;
	this->mWinHeapHandle = nullptr;
	privClearInfo();

	this->pMem = nullptr;
}

void Heap::SetInfoName(const char * const Name)
{
	// Name cannot be null
	assert(Name != nullptr);

	// Copy Name into mInfo.Name
	memcpy_s(this->mInfo.Name, Heap::NameNumChar, Name, Heap::NameNumChar);
}


void Heap::privClearInfo()
{
	this->mInfo.CurrBytesUsed = 0;;
	this->mInfo.PeakBytesUsed = 0;
	this->mInfo.CurrNumAlloc = 0;
	this->mInfo.PeakNumAlloc = 0;
	this->mInfo.StartAddr = 0;
	this->mInfo.EndAddr = 0;
	this->mInfo.TotalSize = 0;

	memset(this->mInfo.Name, 0x0, Heap::NameLength);
}

Heap::Heap(Mem *pMem, HANDLE heapH, unsigned int heapSize, const char * const Name)
{
	this->pBlkHead = nullptr;
	this->mType = Heap::Type::Normal;
	this->mWinHeapHandle = heapH;
	
	privClearInfo();
	this->mInfo.TotalSize = heapSize;
	this->mInfo.StartAddr = (unsigned int) this;
	this->mInfo.EndAddr = (unsigned int) this + heapSize;
	
	SetInfoName(Name);

	this->pMem = pMem;
}

void Heap::GetInfo( Info &retInfo)
{
	retInfo = this->mInfo;
};

Block *Heap::GetTrackingHead()
{
	return this->pBlkHead;
}

Heap *Heap::DebugGetNext() const
{
	return this->GetNextHeap();
};

Heap *Heap::DebugGetPrev() const
{
	return this->GetPrevHeap();
}

void * Heap::protAllocateBlock(size_t blockSize)
{
	// Allocate space on Win32 heap for tracking block and return it
	return (void *)Win32Wrapper::Win32BlockAlloc(this->mWinHeapHandle, blockSize);
}

void Heap::protFreeBlock(void * pBlock)
{
	// Free block from Win32 heap
	Win32Wrapper::Win32BlockFree(this->mWinHeapHandle, pBlock);
}

void Heap::protDestroyHeap()
{
	// Destroy Win32 heap
	Win32Wrapper::Win32HeapDestroy(this->mWinHeapHandle);
}

void Heap::protAddBlock(Block * pBlock)
{
	// pBlock cannot be null
	assert(pBlock != nullptr);

	BlockSAP *pBlockSAP = (BlockSAP *)pBlock;
	BlockSAP *pHeadSAP = (BlockSAP *)this->pBlkHead;

	// Add block to empty list
	if (this->pBlkHead == nullptr)
	{
		this->pBlkHead = pBlock;
	}
	else
	{
		// Push to front of list
		pBlockSAP->SetHeapNextInterface(this->pBlkHead);
		pHeadSAP->SetHeapPrevInterface(pBlock);
		this->pBlkHead = pBlock;
	}
}

void Heap::protRemoveBlock(Block * pBlock)
{
	BlockSAP *pBlockSAP = nullptr;
	BlockSAP *pHeadSAP = nullptr;

	// Remove from front
	if (this->pBlkHead == pBlock)
	{
		this->pBlkHead = pBlock->GetHeapNext();
		// More in list
		if (this->pBlkHead != nullptr)
		{
			pHeadSAP = (BlockSAP *)this->pBlkHead;
			pHeadSAP->SetHeapPrevInterface(nullptr);
		}
	}
	// Remove from end
	else if (pBlock->GetHeapNext() == nullptr)
	{
		// Set prev's heap next pointer
		pBlockSAP = (BlockSAP *)pBlock->GetHeapPrev();
		pBlockSAP->SetHeapNextInterface(pBlock->GetHeapNext());
	}
	// Remove from middle
	else
	{
		// Set prev's heap next pointer
		pBlockSAP = (BlockSAP *)pBlock->GetHeapPrev();
		pBlockSAP->SetHeapNextInterface(pBlock->GetHeapNext());
		// Set next's heap prev pointer
		pBlockSAP = (BlockSAP *)pBlock->GetHeapNext();
		pBlockSAP->SetHeapPrevInterface(pBlock->GetHeapPrev());
	}

	// Set pBlock pointers to null
	pBlockSAP = (BlockSAP *)pBlock;
	pBlockSAP->SetHeapNextInterface(nullptr);
	pBlockSAP->SetHeapPrevInterface(nullptr);
}

void Heap::protIncrementAllocInfo(unsigned int size)
{
	this->mInfo.CurrBytesUsed += size;
	this->mInfo.CurrNumAlloc++;

	if (this->mInfo.CurrBytesUsed > this->mInfo.PeakBytesUsed)
	{
		this->mInfo.PeakBytesUsed += size;
	}
	if (this->mInfo.CurrNumAlloc > this->mInfo.PeakNumAlloc)
	{
		this->mInfo.PeakNumAlloc++;
	}
}

void Heap::protDecrementAllocInfo(unsigned int size)
{
	this->mInfo.CurrBytesUsed -= size;
	this->mInfo.CurrNumAlloc--;
}


// ---  End of File ---------------
