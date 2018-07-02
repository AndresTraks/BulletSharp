#include "StdAfx.h"

#ifdef BT_DEBUG_MEMORY_ALLOCATIONS

#include "AlignedAllocator.h"

extern int gNumAlignedAllocs;
extern int gNumAlignedFree;

int AlignedAllocator::NumAlignedAllocs::get()
{
	return gNumAlignedAllocs;
}

int AlignedAllocator::NumAlignedFrees::get()
{
	return gNumAlignedFree;
}

#endif
