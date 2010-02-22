#include "StdAfx.h"

#include "OverlappingPairCache.h"

OverlappingPairCache::OverlappingPairCache(btOverlappingPairCache* pairCache)
: OverlappingPairCallback(pairCache)
{
}

btOverlappingPairCache* OverlappingPairCache::UnmanagedPointer::get()
{
	return (btOverlappingPairCache*)OverlappingPairCallback::UnmanagedPointer;
}
