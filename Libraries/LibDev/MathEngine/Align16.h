#ifndef ALIGN_16_H
#define ALIGN_16_H

#include "MemEngine.h"

class Align16
{
public:
	void *operator new(size_t size, Heap *pHeap, char *inName, int lineNum)
	{
		// Calls new in Memory System
		// Using char type to accurately get size of data coming in: char(1 byte) * size(n bytes)
		char *p = new(pHeap, Mem::Align::Byte_16, inName, lineNum) char[size];
		return (void *)p;
	}

	void *operator new[](size_t size, Heap *pHeap, char *inName, int lineNum)
	{
		// Calls new in Memory System
		// Using char type to accurately get size of data coming in: char(1 byte) * size(n bytes)
		char *p = new(pHeap, Mem::Align::Byte_16, inName, lineNum) char[size];
		return (void *)p;
	}

	// These delete overloads need to be defined to match overloaded new
	void operator delete(void *p, Heap *, char *, int)
	{
		delete p;
	}
	void operator delete[](void *p, Heap *, char *, int)
	{
		delete p;
	}

	// These delete overloads are actually called
	void operator delete(void *p)
	{
		// Calls delete in Memory System
		delete p;
	}
	void operator delete[](void *p)
	{
		// Calls delete in Memory System
		delete p;
	}
};

#endif