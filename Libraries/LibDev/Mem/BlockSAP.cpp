
#include "BlockSAP.h"

BlockSAP::BlockSAP(char * name, int lineNum, unsigned int allocSize, int allocIndex)
	: Block(name, lineNum, allocSize, allocIndex)
{
}

void BlockSAP::SetHeapNextInterface(Block * pBlock)
{
	this->protSetHeapNext(pBlock);
}

void BlockSAP::SetHeapPrevInterface(Block * pBlock)
{
	this->protSetHeapPrev(pBlock);
}

void BlockSAP::SetGlobalNextInterface(Block * pBlock)
{
	this->protSetGlobalNext(pBlock);
}

void BlockSAP::SetGlobalPrevInterface(Block * pBlock)
{
	this->protSetGlobalPrev(pBlock);
}

void BlockSAP::PrintBlockInfoInterface()
{
	this->protPrintBlockInfo();
}
