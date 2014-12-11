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

OverlapFilterCallback^ OverlapFilterCallback::GetManaged(btOverlapFilterCallback* callback)
{
	return GetObjectFromTable(OverlapFilterCallback, callback);
}

OverlapFilterCallback::~OverlapFilterCallback()
{
	this->!OverlapFilterCallback();
}

OverlapFilterCallback::!OverlapFilterCallback()
{
	if (this->IsDisposed)
		return;

	ObjectTable::Remove(_native);
	//delete _native;
	_native = NULL;
}

OverlapFilterCallback::OverlapFilterCallback()
{
	_native = new OverlapFilterCallbackWrapper(this);
	BulletSharp::ObjectTable::Add(this, _native);
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
	btOverlapCallback** btCallbacks = new btOverlapCallback*[callbacks->Length];
	int i;
	for (i=0; i<callbacks->Length; i++)
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

HashedOverlappingPairCache::HashedOverlappingPairCache(btHashedOverlappingPairCache* native)
	: OverlappingPairCache(native, true)
{
}

HashedOverlappingPairCache::HashedOverlappingPairCache()
	: OverlappingPairCache(new btHashedOverlappingPairCache(), false)
{
}

bool HashedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return Native->needsBroadphaseCollision(proxy0->_native, proxy1->_native);
}

int HashedOverlappingPairCache::Count::get()
{
	return Native->GetCount();
}

OverlapFilterCallback^ HashedOverlappingPairCache::OverlapFilterCallback::get()
{
	return BulletSharp::OverlapFilterCallback::GetManaged(Native->getOverlapFilterCallback());
}
void HashedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	Native->setOverlapFilterCallback(value->_native);
}


SortedOverlappingPairCache::SortedOverlappingPairCache(btSortedOverlappingPairCache* native)
	: OverlappingPairCache(native, true)
{
}

SortedOverlappingPairCache::SortedOverlappingPairCache()
	: OverlappingPairCache(new btSortedOverlappingPairCache(), false)
{
}

bool SortedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1)
{
	return Native->needsBroadphaseCollision(proxy0->_native, proxy1->_native);
}

OverlapFilterCallback^ SortedOverlappingPairCache::OverlapFilterCallback::get()
{
	return BulletSharp::OverlapFilterCallback::GetManaged(Native->getOverlapFilterCallback());
}
void SortedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	Native->setOverlapFilterCallback(value->_native);
}


NullPairCache::NullPairCache(btNullPairCache* native)
	: OverlappingPairCache(native, true)
{
}

NullPairCache::NullPairCache()
	: OverlappingPairCache(new btNullPairCache(), false)
{
}


OverlapFilterCallbackWrapper::OverlapFilterCallbackWrapper(OverlapFilterCallback^ callback)
{
	_callback = callback;
}

bool OverlapFilterCallbackWrapper::needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const
{
	return _callback->NeedBroadphaseCollision(BroadphaseProxy::GetManaged(proxy0), BroadphaseProxy::GetManaged(proxy1));
}
