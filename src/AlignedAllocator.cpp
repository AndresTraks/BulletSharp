#include "StdAfx.h"

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
