//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Trace.h"

#include "Block.h"

#define STUB_PLEASE_REPLACE(x) (x)

Block::Block(char * name, int lineNum, unsigned int allocSize, int allocIndex)
{
	this->pHeapNext = nullptr;
	this->pHeapPrev = nullptr;
	this->pGlobalNext = nullptr;
	this->pGlobalPrev = nullptr;
	
	// Need to parse name to only get file name with directory path
	// Go to the last occurence of '\\' in string
	char *fileName = strrchr(name, '\\');

	// If fileName is NULL
	if(fileName == 0)
	{
		// Then name has no '\\' and is just a file name with no relative path
		fileName = name;
	}
	else
	{
		// name has relative path so fileName is not NULL
		// Get rid of '\\' at beginning of fileName by incrementing pointer
		fileName++;
	}

	// Set mFileName char[] to 0x0
	memset(this->mFileName, 0x0, NameLength);
	// Copy file name to mFileName
	memcpy_s(this->mFileName, NameLength, fileName, NameLength);

	this->mLineNum = lineNum;
	this->mAllocIndex = allocIndex;
	this->mAllocSize = allocSize;

	this->pSecret = this;
}


void Block::protSetHeapNext(Block * pBlock)
{
	this->pHeapNext = pBlock;
}

void Block::protSetHeapPrev(Block * pBlock)
{
	this->pHeapPrev = pBlock;
}

void Block::protSetGlobalNext(Block * pBlock)
{
	this->pGlobalNext = pBlock;
}

void Block::protSetGlobalPrev(Block * pBlock)
{
	this->pGlobalPrev = pBlock;
}

void Block::protPrintBlockInfo()
{
	Trace::out("%s(%d) : {%d} block at %p, %u bytes\n", 
			   this->mFileName, this->mLineNum, this->mAllocIndex, this, this->mAllocSize);
}

Block *Block::GetHeapNext()
{
	return this->pHeapNext;
}

Block *Block::GetHeapPrev()
{
	return this->pHeapPrev;
}

Block *Block::GetGlobalNext()
{
	return this->pGlobalNext;
}

Block *Block::GetGlobalPrev()
{
	return this->pGlobalPrev;
}

char *Block::GetFileName()
{
	return this->mFileName;
}

int Block::GetLineNum()
{
	return this->mLineNum;
}

int Block::GetAllocIndex()
{
	return this->mAllocIndex;
}

unsigned int Block::GetAllocSize()
{
	return this->mAllocSize;
}

// ---  End of File ---------------
