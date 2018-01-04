//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef GLOBAL_NEW_H
#define GLOBAL_NEW_H

#include "Mem.h"

// forward declaration
class Heap;

   // overloaded new/delete
   void * operator new( size_t inSize, Heap *inHeap, Mem::Align align, char *inName, int lineNum);
   void operator delete( void *p, Heap *inHeap, Mem::Align align, char *inName, int lineNum );

   void * operator new[]( size_t inSize ,Heap *pHeap, Mem::Align align, char *inName, int lineNum );
   void operator delete[]( void *p,Heap *pHeap, Mem::Align align, char *inName, int lineNum );

   // Your new system needs to coexist with existing new/delete()
   // simple new/delete is used in the unit test fixture.
   // welcome to memory system development

   void * operator new( size_t inSize );
   void operator delete( void *p );

    void * operator new[]( size_t inSize );
    void operator delete[]( void *p );

#endif

// ---  End of File ---------------
