#include "MemSAP.h"

void * MemSAP::BlockCreateInterface(size_t inSize, Heap * pHeap, Mem::Align align, char * inName, int lineNum)
{
	return Mem::protBlockCreate(inSize, pHeap, align, inName, lineNum);
}

void MemSAP::BlockDestroyInterface(Heap * pHeap, void * p)
{
	Mem::protBlockDestroy(pHeap, p);
}
