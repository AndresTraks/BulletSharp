#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "OverlappingPairCallback.h"
#ifndef DISABLE_UNCOMMON
#include "GhostObject.h"
#endif

OverlappingPairCallback::OverlappingPairCallback(btOverlappingPairCallback* native)
{
	_native = native;
	ObjectTable::Add(this, _native);
}

OverlappingPairCallback^ OverlappingPairCallback::GetManaged(btOverlappingPairCallback* pairCallback)
{
	if (ObjectTable::Contains((intptr_t)pairCallback))
		return ObjectTable::GetObject<OverlappingPairCallback^>((intptr_t)pairCallback);

	if (pairCallback == 0)
		return nullptr;

#ifndef DISABLE_UNCOMMON
	btGhostPairCallback* ghostPairCallback = dynamic_cast<btGhostPairCallback*>(pairCallback);
	if (ghostPairCallback)
		return gcnew GhostPairCallback(ghostPairCallback);
#endif

	btSortedOverlappingPairCache* sortedPairCache = dynamic_cast<btSortedOverlappingPairCache*>(pairCallback);
	if (sortedPairCache)
		return gcnew SortedOverlappingPairCache(sortedPairCache);

	btNullPairCache* nullPairCache = dynamic_cast<btNullPairCache*>(pairCallback);
	if (nullPairCache)
		return gcnew NullPairCache(nullPairCache);

	btHashedOverlappingPairCache* pairCache = dynamic_cast<btHashedOverlappingPairCache*>(pairCallback);
	if (pairCache)
		return gcnew HashedOverlappingPairCache(pairCache);

	throw gcnew InvalidOperationException("Unknown pairCallback");
}

OverlappingPairCallback::~OverlappingPairCallback()
{
	this->!OverlappingPairCallback();
}

OverlappingPairCallback::!OverlappingPairCallback()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	ObjectTable::Remove(_native);
	_native = NULL;

	OnDisposed(this, nullptr);
}

BroadphasePair^ OverlappingPairCallback::AddOverlappingPair(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(_native->addOverlappingPair(proxy0->_native, proxy1->_native));
}

IntPtr OverlappingPairCallback::RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
	Dispatcher^ dispatcher)
{
	return IntPtr(_native->removeOverlappingPair(proxy0->_native, proxy1->_native, dispatcher->_native));
}

void OverlappingPairCallback::RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0,
	Dispatcher^ dispatcher)
{
	_native->removeOverlappingPairsContainingProxy(proxy0->_native, dispatcher->_native);
}

bool OverlappingPairCallback::IsDisposed::get()
{
	return (_native == NULL);
}
