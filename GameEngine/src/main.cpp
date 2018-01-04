#include "MemEngine.h"
#include "Game.h"

Heap *pHeap = 0;
Game *pGame = 0;

int CALLBACK WinMain(HINSTANCE , HINSTANCE,  LPSTR , int )                  
{
	Mem::Initialize();

	Mem::Code result;
	result = Mem::HeapCreate(pHeap, 10 * 1024, "MainHeap");
	assert(result == Mem::Code::OK);

	pGame = new Game("Fresh New Window", 800, 600);
    pGame->Run();

	Mem::Info memInfo;
	Mem::GetInfo(memInfo);

	Trace::out("\n\n***************  MEM INFO  **********************\n");
	Trace::out("Bytes Used: %d, Heap Count: %d, Num Allocations: %d, Alloc Index: %d\n", 
				memInfo.CurrBytesUsed, memInfo.CurrHeapCount, memInfo.CurrNumAlloc, memInfo.CurrAllocIndex);
	Trace::out("Peak Bytes Used: %d, Peak Heap Count: %d, Peak Num Allocations: %d\n", 
				memInfo.PeakBytesUsed, memInfo.PeakHeapCount, memInfo.PeakNumAlloc);

	Heap::Info heapInfo;
	pHeap->GetInfo(heapInfo);

	Trace::out("\n***************  HEAP INFO (Before Heap Destroy) **********************\n");
	Trace::out("Name: %s, Bytes Used: %d, Num Allocations: %d, Total Size: %u, Start Addr: 0x%u, End Addr: 0x%u \n", 
				heapInfo.Name, heapInfo.CurrBytesUsed, heapInfo.CurrNumAlloc, heapInfo.TotalSize, heapInfo.StartAddr, heapInfo.EndAddr);
	Trace::out("Peak Bytes Used: %d, Peak Num Allocations: %d\n\n",
				heapInfo.PeakBytesUsed, memInfo.PeakNumAlloc);

	Heap *pHeapHead = Mem::DebugGetHeapHead();

	assert(pHeapHead == pHeap);

	Mem::HeapDestroy(pHeap);

	Mem::GetInfo(memInfo);

	Trace::out("\n***************  MEM INFO (After Heap Destroy)  **********************\n");
	Trace::out("Bytes Used: %d, Heap Count: %d, Num Allocations: %d, Alloc Index: %d\n",
				memInfo.CurrBytesUsed, memInfo.CurrHeapCount, memInfo.CurrNumAlloc, memInfo.CurrAllocIndex);
	Trace::out("Peak Bytes Used: %d, Peak Heap Count: %d, Peak Num Allocations: %d\n",
				memInfo.PeakBytesUsed, memInfo.PeakHeapCount, memInfo.PeakNumAlloc);

	Mem::Destroy();

    return 0;                                       
}

// ---  End of File ---------------
