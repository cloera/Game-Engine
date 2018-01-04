//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include "Mem.h"
#include "MemSAP.h"
#include "Heap.h"
#include "Block.h"

#include "GlobalNew.h"

#define STUB_PLEASE_REPLACE(x) (x)

// operator new
void * operator new( size_t inSize, Heap *pHeap, Mem::Align align, char *inName, int lineNum )
{
	// Create Block and get pointer to memory
	void *pAlignedAlloc = MemSAP::BlockCreateInterface(inSize, pHeap, align, inName, lineNum);

	// Return address where raw memory starts
	return pAlignedAlloc;
}

void * operator new( size_t inSize )
{
	void *p = malloc( inSize );
	return p;
}

// operator delete
void operator delete( void *p, Heap *pHeap, Mem::Align align, char *inName, int lineNum)
{
	STUB_PLEASE_REPLACE(p);
	STUB_PLEASE_REPLACE(pHeap);
	STUB_PLEASE_REPLACE(align);
	STUB_PLEASE_REPLACE(inName);
	STUB_PLEASE_REPLACE(lineNum);
}

// operator delete
void operator delete( void *p )
{
	// Get heap using address of *p
	Heap *pHeap = nullptr;
	Mem::GetHeapByAddr(pHeap, p);

	// Is *p in our memory system?
	if (pHeap != nullptr)
	{
		// Destroy Block
		MemSAP::BlockDestroyInterface(pHeap, p);
	}
	else
	{
		// No. call free
		free(p);
	}
}

void * operator new[]( size_t inSize ,Heap *pHeap, Mem::Align align, char *inName, int lineNum )
{
	// Create Block and get pointer to memory
	void *pAlignedAlloc = MemSAP::BlockCreateInterface(inSize, pHeap, align, inName, lineNum);

	// Return address where raw memory starts
	return pAlignedAlloc;

}

void operator delete[]( void *p,Heap *pHeap, Mem::Align align, char *inName, int lineNum )
{
	STUB_PLEASE_REPLACE(p);
	STUB_PLEASE_REPLACE(pHeap);
	STUB_PLEASE_REPLACE(align);
	STUB_PLEASE_REPLACE(inName);
	STUB_PLEASE_REPLACE(lineNum);
}

void * operator new[]( size_t inSize )
{
	void *p = malloc( inSize );
	return p;
}

void operator delete[]( void *p )
{
	// Get heap using address of *p
	Heap *pHeap = nullptr;
	Mem::GetHeapByAddr(pHeap, p);

	// Is *p in our memory system?
	if (pHeap != nullptr)
	{
		// Destroy Block
		MemSAP::BlockDestroyInterface(pHeap, p);
	}
	else
	{
		// No. call free
		free(p);
	}


	//free(p);
}

// ---  End of File ---------------
