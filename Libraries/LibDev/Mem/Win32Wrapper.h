#ifndef WIN32WRAPPER_H
#define WIN32WRAPPER_H

#include <assert.h>
#include "Trace.h"

class Win32Wrapper
{

public:

	/*************************************
	Creates a heap using Win32's HeapCreate()
	Returns HANDLE to heap
	Default: Growable heap. No flag options set
	**************************************/
	static HANDLE Win32HeapCreate(SIZE_T initHeapBytes, SIZE_T maxHeapBytes = 0x0, DWORD flagOptions = 0x0)
	{
		HANDLE heapH = HeapCreate(flagOptions, initHeapBytes, maxHeapBytes);

		// Was HANDLE returned by HeapCreate null?
		if (heapH == 0)
		{
			Trace::out("Failed to create heap. Error code: %d\n", GetLastError());
			assert(heapH != 0);
		}

		// For Debugging
		//PrintHeapInfo(heapH);

		return heapH;
	}

	/*************************************
	Allocates block from Win32 heap using HeapAlloc()
	Returns reference to where block was allocated
	Default: Allocated block is set to zero
	**************************************/
	static LPVOID Win32BlockAlloc(HANDLE &heapH, SIZE_T bytesToAllocate, DWORD flagOptions = 0x8)
	{
		// HANDLE cannot be null
		assert(heapH != 0);

		// allocate block on heap
		LPVOID pOutBlock = HeapAlloc(heapH, flagOptions, bytesToAllocate);

		// Was allocation successful or not?
		if (pOutBlock == 0)
		{
			Trace::out("Could not allocate %u bytes of memory\n\n", bytesToAllocate);
		}

		// For Debugging
		//PrintHeapInfo(heapH);

		return pOutBlock;
	}

	/************************************
	Free allocated block using HeapFree()
	Returns BOOL: if FALSE then block was not freed else it was freed successfully
	Default: No flag options
	*************************************/
	static BOOL Win32BlockFree(HANDLE &heapH, LPVOID &pAllocBlock, DWORD flagOptions = 0x0)
	{
		// HANDLE cannot be null
		assert(heapH != 0);
		// Block that is going to be freed should not be null
		assert(pAllocBlock != 0);

		BOOL isFree = HeapFree(heapH, flagOptions, pAllocBlock);

		// Did HeapFree not free block successfully?
		if (isFree == 0)
		{
			Trace::out("Failed to free block. Error code: %d\n", GetLastError());
		}

		// For Debugging
		//PrintHeapInfo(heapH);

		return isFree;
	}

	/*********************************
	Destroys Heap that was created with HeapCreate()
	Returns BOOL: if FALSE then heap was not destoryed else successful
	**********************************/
	static BOOL Win32HeapDestroy(HANDLE &heapH)
	{
		BOOL isDestroyed = HeapDestroy(heapH);

		if (isDestroyed == 0)
		{
			Trace::out("Failed to destroy heap. Error code: %d\n", GetLastError());
		}
		return isDestroyed;
	}


	/*********************************
	Walks Heap and prints all info about heap
	**********************************/
	static void PrintHeapInfo(HANDLE heapH)
	{
		assert(heapH != 0);

		PROCESS_HEAP_ENTRY Entry;
		Entry.lpData = 0;

		// Traverse heap and collect about heap
		while (HeapWalk(heapH, &Entry) != FALSE) {
			if ((Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0) {
				Trace::out("Allocated block");

				if ((Entry.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0) {
					Trace::out(", movable with HANDLE %#p", Entry.Block.hMem);
				}

				if ((Entry.wFlags & PROCESS_HEAP_ENTRY_DDESHARE) != 0) {
					Trace::out(", DDESHARE");
				}
			}
			else if ((Entry.wFlags & PROCESS_HEAP_REGION) != 0) {
				Trace::out("Region\n  %d bytes committed\n", Entry.Region.dwCommittedSize);
				Trace::out("  %d bytes uncommitted\n  First block address: %#p\n", Entry.Region.dwUnCommittedSize, Entry.Region.lpFirstBlock);
				Trace::out("  Last block address: %#p\n", Entry.Region.lpLastBlock);
			}
			else if ((Entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0) {
				Trace::out("Uncommitted range\n");
			}
			else {
				Trace::out("Block\n");
			}

			Trace::out("  Data portion begins at: %#p\n  Size: %d bytes\n", Entry.lpData, Entry.cbData);
			Trace::out("  Overhead: %d bytes\n  Region index: %d\n\n", Entry.cbOverhead, Entry.iRegionIndex);
		}
		DWORD LastError = GetLastError();
		if (LastError != ERROR_NO_MORE_ITEMS) {
			Trace::out("HeapWalk failed with LastError %d.\n", LastError);
		}
	}

};


#endif
