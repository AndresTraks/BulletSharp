#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

OverlapCallback::~OverlapCallback()
{
	this->!OverlapCallback();
}

OverlapCallback::!OverlapCallback()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

bool OverlapCallback::ProcessOverlap(BroadphasePair^ pair)
{
	return _native->processOverlap(*pair->_native);
}

bool OverlapCallback::IsDisposed::get()
{
	return (_native == NULL);
}


OverlapFilterCallback::OverlapFilterCallback(btOverlapFilterCallback* native)
{
	_native = native;
}

OverlapFilterCallback::~OverlapFilterCallback()
{
	this->!OverlapFilterCallback();
}

OverlapFilterCallback::!OverlapFilterCallback()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

OverlapFilterCallback::OverlapFilterCallback()
{
	_native = new OverlapFilterCallbackWrapper(this);
}

bool OverlapFilterCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#define Native static_cast<btOverlappingPairCache*>(_native)

OverlappingPairCache::OverlappingPairCache(btOverlappingPairCache* native, bool preventDelete)
	: OverlappingPairCallback(native, preventDelete)
{
}

void OverlappingPairCache::CleanOverlappingPair(BroadphasePair^ pair, Dispatcher^ dispatcher)
{
	Native->cleanOverlappingPair(*pair->_native, dispatcher->_native);
}

void OverlappingPairCache::CleanProxyFromPairs(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	Native->cleanProxyFromPairs(proxy->_native, dispatcher->_native);
}

BroadphasePair^ OverlappingPairCache::FindPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(Native->findPair(proxy0->_native, proxy1->_native));
}

void OverlappingPairCache::ProcessAllOverlappingPairs(array<OverlapCallback^>^ callbacks,
	Dispatcher^ dispatcher)
{
	int nCallbacks = callbacks->Length;
	btOverlapCallback** btCallbacks = new btOverlapCallback*[nCallbacks];
	int i;
	for (i = 0; i<nCallbacks; i++)
		btCallbacks[i] = callbacks[i]->_native;
	Native->processAllOverlappingPairs(*btCallbacks, dispatcher->_native);
	delete[] btCallbacks;
}

#ifndef DISABLE_INTERNAL
void OverlappingPairCache::SetInternalGhostPairCallback(OverlappingPairCallback^ ghostPairCallback)
{
	_ghostPairCallback = ghostPairCallback;
	Native->setInternalGhostPairCallback(ghostPairCallback->_native);
}
#endif

void OverlappingPairCache::SetOverlapFilterCallback(OverlapFilterCallback^ callback)
{
	Native->setOverlapFilterCallback(GetUnmanagedNullable(callback));
}

void OverlappingPairCache::SortOverlappingPairs(Dispatcher^ dispatcher)
{
	Native->sortOverlappingPairs(dispatcher->_native);
}

bool OverlappingPairCache::HasDeferredRemoval::get()
{
	return Native->hasDeferredRemoval();
}

int OverlappingPairCache::NumOverlappingPairs::get()
{
	return Native->getNumOverlappingPairs();
}

AlignedBroadphasePairArray^ OverlappingPairCache::OverlappingPairArray::get()
{
	btBroadphasePairArray* pairArray = &Native->getOverlappingPairArray();
	ReturnCachedObjectGcnew(AlignedBroadphasePairArray, _overlappingPairArray, pairArray);
}
/*
BroadphasePair^ OverlappingPairCache::OverlappingPairArrayPtr::get()
{
	return Native->getOverlappingPairArrayPtr();
}
*/


#undef Native
#define Native static_cast<btHashedOverlappingPairCache*>(_native)

HashedOverlappingPairCache::HashedOverlappingPairCache(btHashedOverlappingPairCache* native, bool preventDelete)
	: OverlappingPairCache(native, preventDelete)
{
}

HashedOverlappingPairCache::HashedOverlappingPairCache()
	: OverlappingPairCache(new btHashedOverlappingPairCache(), false)
{
}

BroadphasePair^ HashedOverlappingPairCache::AddOverlappingPair(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(_native->addOverlappingPair(proxy0->_native, proxy1->_native));
}

bool HashedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return Native->needsBroadphaseCollision(proxy0->_native, proxy1->_native);
}

IntPtr HashedOverlappingPairCache::RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
	Dispatcher^ dispatcher)
{
	return IntPtr(_native->removeOverlappingPair(proxy0->_native, proxy1->_native, dispatcher->_native));
}

void HashedOverlappingPairCache::RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0,
	Dispatcher^ dispatcher)
{
	_native->removeOverlappingPairsContainingProxy(proxy0->_native, dispatcher->_native);
}

int HashedOverlappingPairCache::Count::get()
{
	return Native->GetCount();
}

OverlapFilterCallback^ HashedOverlappingPairCache::OverlapFilterCallback::get()
{
	return _overlapFilterCallback;
}
void HashedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	_overlapFilterCallback = value;
	Native->setOverlapFilterCallback(value->_native);
}


SortedOverlappingPairCache::SortedOverlappingPairCache()
	: OverlappingPairCache(new btSortedOverlappingPairCache(), false)
{
}

BroadphasePair^ SortedOverlappingPairCache::AddOverlappingPair(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(_native->addOverlappingPair(proxy0->_native, proxy1->_native));
}

bool SortedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return Native->needsBroadphaseCollision(proxy0->_native, proxy1->_native);
}

IntPtr SortedOverlappingPairCache::RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
	Dispatcher^ dispatcher)
{
	return IntPtr(_native->removeOverlappingPair(proxy0->_native, proxy1->_native, dispatcher->_native));
}

void SortedOverlappingPairCache::RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0,
	Dispatcher^ dispatcher)
{
	_native->removeOverlappingPairsContainingProxy(proxy0->_native, dispatcher->_native);
}

OverlapFilterCallback^ SortedOverlappingPairCache::OverlapFilterCallback::get()
{
	return _overlapFilterCallback;
}
void SortedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	_overlapFilterCallback = value;
	Native->setOverlapFilterCallback(value->_native);
}


NullPairCache::NullPairCache()
	: OverlappingPairCache(new btNullPairCache(), false)
{
}

BroadphasePair^ NullPairCache::AddOverlappingPair(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(_native->addOverlappingPair(proxy0->_native, proxy1->_native));
}

IntPtr NullPairCache::RemoveOverlappingPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1,
	Dispatcher^ dispatcher)
{
	return IntPtr(_native->removeOverlappingPair(proxy0->_native, proxy1->_native, dispatcher->_native));
}

void NullPairCache::RemoveOverlappingPairsContainingProxy(BroadphaseProxy^ proxy0,
	Dispatcher^ dispatcher)
{
	_native->removeOverlappingPairsContainingProxy(proxy0->_native, dispatcher->_native);
}


OverlapFilterCallbackWrapper::OverlapFilterCallbackWrapper(OverlapFilterCallback^ callback)
{
	_callback = callback;
}

bool OverlapFilterCallbackWrapper::needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const
{
	return _callback->NeedBroadphaseCollision(BroadphaseProxy::GetManaged(proxy0), BroadphaseProxy::GetManaged(proxy1));
}
