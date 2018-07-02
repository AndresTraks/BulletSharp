#include "StdAfx.h"

#include "AlignedAllocator.h"

#ifdef BT_DEBUG_MEMORY_ALLOCATIONS
extern int gNumAlignedAllocs;
extern int gNumAlignedFree;
#endif

int AlignedAllocator::NumAlignedAllocs::get()
{
#ifdef BT_DEBUG_MEMORY_ALLOCATIONS
	return gNumAlignedAllocs;
#else
	throw gcnew NotSupportedException("Bullet has not been compiled with BT_DEBUG_MEMORY_ALLOCATIONS defined.");
#endif
}

int AlignedAllocator::NumAlignedFrees::get()
{
#ifdef BT_DEBUG_MEMORY_ALLOCATIONS
	return gNumAlignedFree;
#else
	throw gcnew NotSupportedException("Bullet has not been compiled with BT_DEBUG_MEMORY_ALLOCATIONS defined.");
#endif
}
