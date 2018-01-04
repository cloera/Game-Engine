//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <new>

#include "Mem.h"
#include "HeapSAP.h"
#include "BlockSAP.h"
#include "Win32Wrapper.h"

#define STUB_PLEASE_REPLACE(x) (x)

Mem *Mem::poMemInstance = nullptr;


Mem::Mem()
{
	this->poHead = nullptr;
	this->pGlobalHead = nullptr;
	privClearInfo();
}

Mem::~Mem()
{
	delete this->poMemInstance;
}

// Create the heap.
Mem::Code Mem::HeapCreate(Heap *&newHeap, unsigned int heapSize, const char * const Name)
{
	Mem::Code codeInstance = privHasInstance();

	if (codeInstance == Mem::Code::OK)
	{
		// Get mem instance
		Mem *instance = privGetInstance();

		// Create Win 32 Heap
		HANDLE heapH = Win32Wrapper::Win32HeapCreate(heapSize);

		// If heapH is 
		if (heapH == 0)
			return Mem::Code::ERROR_Heap_Create;

		// Allocate space for Heap object
		unsigned int *pHeapAlloc = (unsigned int *)Win32Wrapper::Win32BlockAlloc(heapH, sizeof(Heap));

		// If pHeapAlloc is null then heap could not be created
		if (pHeapAlloc == 0)
			return Mem::Code::ERROR_Heap_Create;

		// Create new Heap object and place memory in 
		newHeap = (Heap *) new(pHeapAlloc) HeapSAP(instance, heapH, heapSize, Name);

		// Add to list of heaps
		privAddHeapToList(newHeap);

		// Update stats
		privIncrementHeapCount();

		return codeInstance;
	}

	return codeInstance;
}

// Not implemented. Do Not Use.
Mem::Code Mem::HeapCreate(Heap *&newHeap, unsigned int numBlocks, int sizePerBlock, const char * const Name)
{
	Mem::Code codeInstance = privHasInstance();

	if (codeInstance == Mem::Code::OK)
	{
		STUB_PLEASE_REPLACE(newHeap);
		STUB_PLEASE_REPLACE(numBlocks);
		STUB_PLEASE_REPLACE(sizePerBlock);
		STUB_PLEASE_REPLACE(Name);
	}
	return codeInstance;
}

// Initialize the memory system  (Public method)
Mem::Code Mem::Initialize(void)
{
	// Reset singleton
	poMemInstance = nullptr;
	// Initialize Mem singleton
	privGetInstance();

	return privHasInstance();
}

Mem::Code Mem::Destroy(void)
{
	Mem::Code instanceCode = privHasInstance();

	// if instanceCode is OK then nuke memory system
	if (instanceCode == Mem::Code::OK)
	{
		// Get Mem instance
		Mem *instance = privGetInstance();
		// Initialize HeapSAP for method access
		HeapSAP *pHeapSAP = nullptr;

		Trace::out("/******************************************/\n");

		// Print Mem info
		instance->privPrintMem();

		// Do I have data in Global list to delete?
		if (instance->pGlobalHead != nullptr)
		{
			// Temp Heap
			Heap *pTempHeap = nullptr;
			// Current Block in Global list
			Block *pCurrGlobal = instance->pGlobalHead;
			Block *pNextBlock;
			BlockSAP *pBlockSAP;

			Trace::out("|------------- ALLOCATIONS ------------|\n");

			// Loop through list
			while (pCurrGlobal != nullptr)
			{
				// Which heap does this block belong to?
				GetHeapByAddr(pTempHeap, pCurrGlobal);
				// Save next Block
				pNextBlock = pCurrGlobal->GetGlobalNext();
				// Print block info
				pBlockSAP = (BlockSAP *)pCurrGlobal;
				pBlockSAP->PrintBlockInfoInterface();
				// Remove from global list
				privRemoveBlockFromGlobalList(pCurrGlobal);
				// Free block from Win32 heap
				pHeapSAP = (HeapSAP *)pTempHeap;
				pHeapSAP->FreeBlockInterface(pCurrGlobal);
				// Move to next node
				pCurrGlobal = pNextBlock;
			}
			Trace::out("|-------------------------------------------|\n");
		}

		// Do I have data in Heap list to delete?
		if (instance->poHead != nullptr)
		{
			// Current Heap
			Heap *pCurrHeap = instance->poHead;
			Heap *pNextHeap;

			while (pCurrHeap != nullptr)
			{
				// Save next heap
				pNextHeap = pCurrHeap->GetNextHeap();
				// Remove from list
				privRemoveHeapFromList(pCurrHeap);
				// Destroy Win32 heap
				pHeapSAP = (HeapSAP *)pCurrHeap;
				pHeapSAP->DestroyHeapInterface();
				// Move heap pointer
				pCurrHeap = pNextHeap;
			}
		}

		Trace::out("/******************************************/\n");

		instance->pGlobalHead = nullptr;
		instance->mInfo = { 0 };
		instance->poMemInstance = nullptr;
	}
	return instanceCode;
}

Mem::Code Mem::GetInfo(Mem::Info &retInfo)
{
	Mem::Code instanceCode = privHasInstance();

	// If Mem instance is initialized
	if (instanceCode == Mem::Code::OK)
	{
		Mem *instance = privGetInstance();
		// Set mInfo to retInfo and return code
		retInfo = instance->mInfo;
		return instanceCode;
	}
	// Mem not initialized. Return code
	return instanceCode;
}

void Mem::privIncrementHeapCount()
{
	Mem *instance = privGetInstance();

	instance->mInfo.CurrHeapCount++;

	if (instance->mInfo.CurrHeapCount > instance->mInfo.PeakHeapCount)
	{
		instance->mInfo.PeakHeapCount++;
	}
}

void Mem::privDecrementHeapCount()
{
	privGetInstance()->mInfo.CurrHeapCount--;
}

void Mem::privClearInfo()
{
	this->mInfo.CurrAllocIndex = 0;
	this->mInfo.CurrBytesUsed = 0;
	this->mInfo.CurrHeapCount = 0;
	this->mInfo.CurrNumAlloc = 0;
	this->mInfo.PeakBytesUsed = 0;
	this->mInfo.PeakHeapCount = 0;
	this->mInfo.PeakNumAlloc = 0;
}

Heap *Mem::DebugGetHeapHead()
{
	return privGetInstance()->poHead;
}


Block *Mem::DebugGetGlobalTrackingHead()
{
	return privGetInstance()->pGlobalHead;
}

Mem::Code Mem::HeapDestroy(Heap *inHeap)
{
	assert(inHeap != nullptr);

	Mem::Code codeInstance = privHasInstance();

	if (codeInstance == Mem::Code::OK)
	{
		// Get HeapSAP from inHeap
		HeapSAP *pHeapSAP = (HeapSAP *)inHeap;
		// Get root block of heap list
		Block *pCurrBlock = (Block *)pHeapSAP->GetTrackingHead();
		Block *pTempBlock;

		// Traverse heap list and remove blocks
		while (pCurrBlock != nullptr)
		{
			// Save next block
			pTempBlock = pCurrBlock->GetHeapNext();
			// Update Alloc stats
			protDecrementAllocInfo(pCurrBlock->GetAllocSize());
			// Remove from global list
			privRemoveBlockFromGlobalList(pCurrBlock);
			// Remove from heap list
			pHeapSAP->RemoveBlockInterface(pCurrBlock);
			// Free block
			pHeapSAP->FreeBlockInterface(pCurrBlock);
			// Move to next block
			pCurrBlock = pTempBlock;
		}

		// Remove heap from list
		privRemoveHeapFromList(pHeapSAP);

		// Get heap info
		Heap::Info info;
		pHeapSAP->GetInfo(info);

		// Update stats
		privDecrementHeapCount();

		// Destroy Win32 heap
		pHeapSAP->DestroyHeapInterface();
	}
	return codeInstance;
}


Mem::Code Mem::GetHeapByAddr(Heap *&pHeap, void *p)
{
	Mem::Code codeInstance = privHasInstance();

	if (codeInstance == Mem::Code::OK)
	{
		// Get Mem instance
		Mem *instance = privGetInstance();

		// Get head of heap list
		Heap *pCurrHeap = instance->poHead;

		Heap::Info info;

		// Traverse heap list
		while (pCurrHeap != nullptr)
		{
			// Get info for current heap
			pCurrHeap->GetInfo(info);

			// Check to see if the address of *p is between
			// the start and end addresses of any heaps in list
			if ((unsigned int)p > info.StartAddr && (unsigned int)p < info.EndAddr)
			{
				// If *p is in list set current heap to pHeap and break
				pHeap = pCurrHeap;
				break;
			}
			// Move heap pointer
			pCurrHeap = pCurrHeap->GetNextHeap();
		}
	}
	return codeInstance;
}

Mem *Mem::privGetInstance()
{
	// If Mem pointer is nullptr
	if (poMemInstance == nullptr)
	{
		// Initialize it
		poMemInstance = new Mem();
	}
	return poMemInstance;
}

Mem::Code Mem::privHasInstance()
{
	if (poMemInstance != nullptr)
	{
		return Mem::Code::OK;
	}
	return Mem::Code::ERROR_Mem_Not_Initialized;
}

void Mem::privAddHeapToList(Heap * pHeap)
{
	// pHeap cannot be null
	assert(pHeap != nullptr);

	Mem *instance = privGetInstance();

	// Add heap to empty list
	if (instance->poHead == nullptr)
	{
		instance->poHead = pHeap;
	}
	else
	{
		// Push to front of list
		pHeap->SetNextHeap(instance->poHead);
		instance->poHead->SetPrevHeap(pHeap);
		instance->poHead = pHeap;
	}
}

void Mem::privRemoveHeapFromList(Heap *pHeap)
{
	assert(pHeap != nullptr);

	Mem *instance = privGetInstance();

	// Remove from front
	if (instance->poHead == pHeap)
	{
		instance->poHead = pHeap->GetNextHeap();
		// More in list
		if (instance->poHead != nullptr)
		{
			instance->poHead->SetPrevHeap(nullptr);
		}
	}
	// Remove from end
	else if (pHeap->GetNextHeap() == nullptr)
	{
		pHeap->GetPrevHeap()->SetNextHeap(pHeap->GetNextHeap());
	}
	// Remove from middle
	else
	{
		pHeap->GetPrevHeap()->SetNextHeap(pHeap->GetNextHeap());
		pHeap->GetNextHeap()->SetPrevHeap(pHeap->GetPrevHeap());
	}

	// Set pointers to null
	pHeap->SetNextHeap(nullptr);
	pHeap->SetPrevHeap(nullptr);
}

void * Mem::protBlockCreate(size_t inSize, Heap * pHeap, Mem::Align align, char * inName, int lineNum)
{
	// Find allignment padding
	unsigned int padding = Mem::privGetAlignmentPadding(align);

	// Get HeapSAP from Heap
	HeapSAP *pHeapSAP = (HeapSAP *)pHeap;

	// Allocate space on Win32 heap while taking Block size and padding into account
	void *pBlockAlloc = pHeapSAP->AllocateBlockInterface(sizeof(Block) + inSize + padding);

	// placement new on tracking block
	Block *pBlock = pHeapSAP->AddBlockInterface(pBlockAlloc, inName, lineNum, inSize, Mem::privIncrementAllocIndex());

	// attach tracking block to global list
	Mem::privAddBlockToGlobalList(pBlock);

	// update stats
	Mem::protIncrementAllocInfo(inSize);

	// Correct pointer to be aligned with alignment padding.  Pointing to raw memory
	void *pAlignedAlloc = (void *)(((unsigned int)pBlockAlloc + sizeof(Block) + (padding - 1)) & ~(padding - 1));

	// Go up 4 bytes from raw mem to go to new secret address
	char **pNewSecret = (char **)((char *)pAlignedAlloc - sizeof(unsigned int));
	// Set address of Block header to new secret pointer location
	*pNewSecret = (char *)pBlockAlloc;

	// Return address where raw memory starts
	return (void *)pAlignedAlloc;
}

void Mem::protBlockDestroy(Heap * pHeap, void * p)
{
	// Cast *p to unsigned int
	unsigned int *pSecret = (unsigned int *)p;
	// Decrement pSecret by 4 bytes. Should be at Block->pSecret
	--pSecret;
	// Get address stored at pSecret should be start address of Block
	Block *pBlock = (Block *)*pSecret;

	// Get HeapSAP from pBlock
	HeapSAP *pHeapSAP = (HeapSAP *)pHeap;

	// Remove from Heap list
	pHeapSAP->RemoveBlockInterface(pBlock);

	// Remove from Global list
	Mem::privRemoveBlockFromGlobalList(pBlock);

	// Update stats
	Mem::protDecrementAllocInfo(pBlock->GetAllocSize());
	pHeapSAP->DecreAllocInfoInterface(pBlock->GetAllocSize());

	// Free pBlock from Win32 heap
	pHeapSAP->FreeBlockInterface(pBlock);
}

void Mem::privAddBlockToGlobalList(Block * pBlock)
{
	// pBlock cannot be null
	assert(pBlock != nullptr);

	Mem *instance = privGetInstance();
	BlockSAP *pBlockSAP = (BlockSAP *)pBlock;
	BlockSAP *pHeadSAP = (BlockSAP *)instance->pGlobalHead;

	// Add block to empty list
	if (instance->pGlobalHead == nullptr)
	{
		instance->pGlobalHead = pBlock;
	}
	else
	{
		// Push to front of list
		pBlockSAP->SetGlobalNextInterface(instance->pGlobalHead);
		pHeadSAP->SetGlobalPrevInterface(pBlock);
		instance->pGlobalHead = pBlock;
	}
}

void Mem::privRemoveBlockFromGlobalList(Block * pBlock)
{
	assert(pBlock != nullptr);

	Mem *instance = privGetInstance();
	BlockSAP *pBlockSAP = nullptr;
	BlockSAP *pHeadSAP = nullptr;

	// Remove from front
	if (instance->pGlobalHead == pBlock)
	{
		instance->pGlobalHead = pBlock->GetGlobalNext();
		// More in list
		if (instance->pGlobalHead != nullptr)
		{
			pHeadSAP = (BlockSAP *)instance->pGlobalHead;
			pHeadSAP->SetGlobalPrevInterface(nullptr);
		}
	}
	// Remove from end
	else if (pBlock->GetGlobalNext() == nullptr)
	{
		// Set prev's global next pointer
		pBlockSAP = (BlockSAP *)pBlock->GetGlobalPrev();
		pBlockSAP->SetGlobalNextInterface(pBlock->GetGlobalNext());
	}
	// Remove from middle
	else
	{
		// Set prev's global next pointer
		pBlockSAP = (BlockSAP *)pBlock->GetGlobalPrev();
		pBlockSAP->SetGlobalNextInterface(pBlock->GetGlobalNext());
		// Set next's global prev pointer
		pBlockSAP = (BlockSAP *)pBlock->GetGlobalNext();
		pBlockSAP->SetGlobalPrevInterface(pBlock->GetGlobalPrev());
	}

	// Set pBlock pointers to null
	pBlockSAP = (BlockSAP *)pBlock;
	pBlockSAP->SetGlobalNextInterface(nullptr);
	pBlockSAP->SetGlobalPrevInterface(nullptr);
}

void Mem::privPrintMem()
{
	Mem *inst = privGetInstance();

	// If there are blocks in global list then memory is leaking
	if (inst->pGlobalHead != 0)
	{
		Trace::out(">>>>>>>>>>>>>> MEMORY LEAK <<<<<<<<<<<<<<<\n");
		Trace::out("|-------------------------------------------|\n");
		Trace::out("  Number of allocations: %d\n", inst->mInfo.CurrNumAlloc);
		Trace::out("  Bytes in use: %d\n", inst->mInfo.CurrBytesUsed);
		Trace::out("|-------------------------------------------|\n");
	}
	// Else memory is leaking
	else
	{
		Trace::out("|-------------------------------------------|\n");
		Trace::out("|------------   No memory leaks   ----------|\n");
		Trace::out("|-------------------------------------------|\n");
	}
}

unsigned int Mem::privGetAlignmentPadding(Mem::Align alignment)
{
	unsigned int padding = 0;
	switch (alignment)
	{
	case Mem::Align::Byte_4:
		padding = 4u;
		break;
	case Mem::Align::Byte_8:
		padding = 8u;
		break;
	case Mem::Align::Byte_16:
		padding = 16u;
		break;
	case Mem::Align::Byte_32:
		padding = 32u;
		break;
	case Mem::Align::Byte_64:
		padding = 64u;
		break;
	case Mem::Align::Byte_128:
		padding = 128u;
		break;
	case Mem::Align::Byte_256:
		padding = 256u;
		break;
	}

	return padding;
}

void Mem::protIncrementAllocInfo(unsigned int size)
{
	Mem *instance = privGetInstance();

	instance->mInfo.CurrBytesUsed += size;
	instance->mInfo.CurrNumAlloc++;

	if (instance->mInfo.CurrBytesUsed > instance->mInfo.PeakBytesUsed)
	{
		instance->mInfo.PeakBytesUsed += size;
	}
	if (instance->mInfo.CurrNumAlloc > instance->mInfo.PeakNumAlloc)
	{
		instance->mInfo.PeakNumAlloc++;
	}
}

void Mem::protDecrementAllocInfo(unsigned int size)
{
	Mem *instance = privGetInstance();

	instance->mInfo.CurrBytesUsed -= size;
	instance->mInfo.CurrNumAlloc--;
}

int Mem::privIncrementAllocIndex()
{
	// Pre-increment and return index
	return ++privGetInstance()->mInfo.CurrAllocIndex;
}

// ---  End of File ---------------
