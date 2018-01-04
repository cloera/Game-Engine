#ifndef BLOCKSAP_H
#define BLOCKSAP_H

#include "Block.h"

class BlockSAP : public Block
{
public:
	// Specialized constructor
	BlockSAP(char * name, int lineNum, unsigned int allocSize, int allocIndex);

	// Setters
	void SetHeapNextInterface(Block *pBlock);
	void SetHeapPrevInterface(Block *pBlock);
	void SetGlobalNextInterface(Block *pBlock);
	void SetGlobalPrevInterface(Block *pBlock);

	// Helper functions
	void PrintBlockInfoInterface();

};

#endif // !BLOCKSAP_H

