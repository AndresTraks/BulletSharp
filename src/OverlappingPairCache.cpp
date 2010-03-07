#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

OverlappingPairCache::OverlappingPairCache(btOverlappingPairCache* pairCache)
: OverlappingPairCallback(pairCache)
{
}

void OverlappingPairCache::CleanOverlappingPair(BroadphasePair^ pair, Dispatcher^ dispatcher)
{
	UnmanagedPointer->cleanOverlappingPair(*pair->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void OverlappingPairCache::CleanProxyFromPairs(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	UnmanagedPointer->cleanProxyFromPairs(proxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

BroadphasePair^ OverlappingPairCache::FindPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(UnmanagedPointer->findPair(proxy0->UnmanagedPointer, proxy1->UnmanagedPointer));
}

void OverlappingPairCache::SetInternalGhostPairCallback(
	OverlappingPairCallback^ ghostPairCallback)
{
	UnmanagedPointer->setInternalGhostPairCallback(ghostPairCallback->UnmanagedPointer);
}

void OverlappingPairCache::SortOverlappingPairs(Dispatcher^ dispatcher)
{
	UnmanagedPointer->sortOverlappingPairs(dispatcher->UnmanagedPointer);
}

bool OverlappingPairCache::HasDeferredRemoval::get()
{
	return UnmanagedPointer->hasDeferredRemoval();
}

int OverlappingPairCache::NumOverlappingPairs::get()
{
	return UnmanagedPointer->getNumOverlappingPairs();
}

BroadphasePairArray^ OverlappingPairCache::OverlappingPairArray::get()
{
	return gcnew BroadphasePairArray(&UnmanagedPointer->getOverlappingPairArray());
}

btOverlappingPairCache* OverlappingPairCache::UnmanagedPointer::get()
{
	return (btOverlappingPairCache*)OverlappingPairCallback::UnmanagedPointer;
}
