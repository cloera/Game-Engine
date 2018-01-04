//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef MEM_H
#define MEM_H

// forward declaration
class Heap;
class Block;

// Singleton
class Mem
{
public:

	// Constants for the library
	static const unsigned int MAJOR_VERSION = 2;
	static const unsigned int MINOR_VERSION = 0;

	// alignment 
	enum Align
	{
		Byte_4,
		Byte_8,
		Byte_16,
		Byte_32,
		Byte_64,
		Byte_128,
		Byte_256
	};

	// Return codes
	enum Code
	{
		OK,
		ERROR_Heap_Create,
		ERROR_Illegal_Heap,
		ERROR_Mem_Not_Initialized,
		ERROR_Invalid_Addr,
		Dword = 0x7fffffff
	};

	// info structure
	struct Info
	{
		int CurrAllocIndex;
		int PeakHeapCount;
		int CurrHeapCount;
		int PeakNumAlloc;
		int CurrNumAlloc;
		int PeakBytesUsed;
		int CurrBytesUsed;
	};

public:
	// Public Interface ------------------------------   for the customers

	// Initialize the mem system
	static Code Initialize();
	static Code Destroy();

	// Create an Heap from the heap system
	static Code HeapCreate(Heap *&newHeap, unsigned int heapSize, const char * const Name);
	// Not implemented. Do Not Use.
	static Code HeapCreate(Heap *&newHeap, unsigned int numBlocks, int sizePerBlock, const char * const Name);

	// Create an Heap from the heap system
	static Code HeapDestroy(Heap *inHeap);

	// Information
	static Code GetInfo(Info &info);
	static Code GetHeapByAddr(Heap *&pHeap, void *p);
	static Block *DebugGetGlobalTrackingHead(void);

	// Needed for Testings (Not for Customers)
	static Heap *DebugGetHeapHead(void);

	// -----------------------------------------------------------------------------------
	// Add extra data or methods below this line
	// -----------------------------------------------------------------------------------

	~Mem();

protected:
	// Create and destroy blocks allocated on Win32 heap
	static void* protBlockCreate(size_t inSize, Heap *pHeap, Mem::Align align, char *inName, int lineNum);
	static void  protBlockDestroy(Heap *pHeap, void *p);

private:
	// Private constructor for Singleton
	Mem();
	static Mem *privGetInstance();
	static Mem::Code privHasInstance();

	// Adding and removing heap from heap list
	static void privAddHeapToList(Heap *pHeap);
	static void privRemoveHeapFromList(Heap *pHeap);

	// Adding and removing heap from Global list
	static void privAddBlockToGlobalList(Block *pBlock);
	static void privRemoveBlockFromGlobalList(Block *pBlock);

	// Helper methods
	static void privPrintMem();
	static unsigned int privGetAlignmentPadding(Mem::Align alignment);
	static void privIncrementHeapCount();
	static void privDecrementHeapCount();
	static void protIncrementAllocInfo(unsigned int size);
	static void protDecrementAllocInfo(unsigned int size);
	static int privIncrementAllocIndex();
	void privClearInfo();

	// data -----------------------------------------------------------------------
	static Mem		*poMemInstance;
	Heap			*poHead;
	Block			*pGlobalHead;
	Info			mInfo;
};

#endif 

// ---  End of File ---------------
