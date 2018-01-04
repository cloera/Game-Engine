#ifndef HEAPLINK_H
#define HEAPLINK_H

class Heap;

class HeapLink
{
public:
	// Big Four
	HeapLink();
	HeapLink(const HeapLink &in);
	const HeapLink & operator=(const HeapLink &in);
	~HeapLink();

	// Getters and Setters (Accessors)
	Heap* GetNextHeap() const;
	Heap* GetPrevHeap() const;

	void SetNextHeap(Heap *pHeap);
	void SetPrevHeap(Heap *pHeap);

private:
	// data
	Heap	*pHeapNext;
	Heap	*pHeapPrev;

};


#endif // HEAPLINK_H
