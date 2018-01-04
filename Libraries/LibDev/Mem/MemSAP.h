#ifndef MEMSAP_H
#define MEMSAP_H

#include "Mem.h"

class MemSAP : public Mem
{
public:
	// Default constructor should not be used since Mem is a singleton
	MemSAP() = delete;

	// Create and destroy blocks allocated on Win32 heap
	static void* BlockCreateInterface(size_t inSize, Heap *pHeap, Mem::Align align, char *inName, int lineNum);
	static void  BlockDestroyInterface(Heap *pHeap, void *p);

};


#endif // !MEMSAP_H

