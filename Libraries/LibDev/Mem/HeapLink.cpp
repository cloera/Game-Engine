#include "HeapLink.h"

HeapLink::HeapLink()
{
	this->pHeapNext = nullptr;
	this->pHeapPrev = nullptr;
}

HeapLink::HeapLink(const HeapLink & in)
{
	this->pHeapNext = in.pHeapNext;
	this->pHeapPrev = in.pHeapPrev;
}

const HeapLink & HeapLink::operator=(const HeapLink & in)
{
	if (this != &in)
	{
		this->pHeapNext = in.pHeapNext;
		this->pHeapPrev = in.pHeapPrev;
	}
	return *this;
}

HeapLink::~HeapLink()
{
	this->pHeapNext = nullptr;
	this->pHeapPrev = nullptr;
}

Heap * HeapLink::GetNextHeap() const
{
	return this->pHeapNext;
}

Heap * HeapLink::GetPrevHeap() const
{
	return this->pHeapPrev;
}

void HeapLink::SetNextHeap(Heap * pHeap)
{
	this->pHeapNext = pHeap;
}

void HeapLink::SetPrevHeap(Heap * pHeap)
{
	this->pHeapPrev = pHeap;
}
