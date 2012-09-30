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

	OnDisposing(this, nullptr);

	_callback = NULL;

	OnDisposed(this, nullptr);
}

bool OverlapCallback::ProcessOverlap(BroadphasePair^ pair)
{
	return UnmanagedPointer->processOverlap(*pair->UnmanagedPointer);
}

bool OverlapCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btOverlapCallback* OverlapCallback::UnmanagedPointer::get()
{
	return _callback;
}

void OverlapCallback::UnmanagedPointer::set(btOverlapCallback* value)
{
	_callback = value;
}


OverlapFilterCallback::~OverlapFilterCallback()
{
	this->!OverlapFilterCallback();
}

OverlapFilterCallback::!OverlapFilterCallback()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	ObjectTable::Remove(_unmanaged);
	//delete _unmanaged;
	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

OverlapFilterCallback::OverlapFilterCallback()
{
	_unmanaged = new OverlapFilterCallbackWrapper(this);
	BulletSharp::ObjectTable::Add(this, _unmanaged);
}

bool OverlapFilterCallback::IsDisposed::get()
{
	return (_unmanaged == NULL);
}

OverlapFilterCallback::OverlapFilterCallback(btOverlapFilterCallback* callback)
{
	_unmanaged = callback;
}

OverlapFilterCallback^ OverlapFilterCallback::GetManaged(btOverlapFilterCallback* callback)
{
	return GetObjectFromTable(OverlapFilterCallback, callback);
}

btOverlapFilterCallback* OverlapFilterCallback::UnmanagedPointer::get()
{
	return _unmanaged;
}

void OverlapFilterCallback::UnmanagedPointer::set(btOverlapFilterCallback* value)
{
	_unmanaged = value;
}


OverlappingPairCache::OverlappingPairCache(btOverlappingPairCache* pairCache)
: OverlappingPairCallback(pairCache)
{
}

void OverlappingPairCache::CleanOverlappingPair(BroadphasePair^ pair, Dispatcher^ dispatcher)
{
	UnmanagedPointer->cleanOverlappingPair(*pair->UnmanagedPointer, dispatcher->_unmanaged);
}

void OverlappingPairCache::CleanProxyFromPairs(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	UnmanagedPointer->cleanProxyFromPairs(proxy->_unmanaged, dispatcher->_unmanaged);
}

BroadphasePair^ OverlappingPairCache::FindPair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(UnmanagedPointer->findPair(proxy0->_unmanaged, proxy1->_unmanaged));
}

void OverlappingPairCache::ProcessAllOverlappingPairs(array<OverlapCallback^>^ callbacks, Dispatcher^ dispatcher)
{
	btOverlapCallback** btCallbacks = new btOverlapCallback*[callbacks->Length];
	int i;
	for (i=0; i<callbacks->Length; i++)
		btCallbacks[i] = callbacks[i]->UnmanagedPointer;
	UnmanagedPointer->processAllOverlappingPairs(*btCallbacks, dispatcher->_unmanaged);
	delete[] btCallbacks;
}

#ifndef DISABLE_INTERNAL
void OverlappingPairCache::SetInternalGhostPairCallback(OverlappingPairCallback^ ghostPairCallback)
{
	UnmanagedPointer->setInternalGhostPairCallback(ghostPairCallback->UnmanagedPointer);
}
#endif

void OverlappingPairCache::SetOverlapFilterCallback(OverlapFilterCallback^ callback)
{
	UnmanagedPointer->setOverlapFilterCallback(GetUnmanagedNullable(callback));
}

void OverlappingPairCache::SortOverlappingPairs(Dispatcher^ dispatcher)
{
	UnmanagedPointer->sortOverlappingPairs(dispatcher->_unmanaged);
}

bool OverlappingPairCache::HasDeferredRemoval::get()
{
	return UnmanagedPointer->hasDeferredRemoval();
}

int OverlappingPairCache::NumOverlappingPairs::get()
{
	return UnmanagedPointer->getNumOverlappingPairs();
}

AlignedBroadphasePairArray^ OverlappingPairCache::OverlappingPairArray::get()
{
	btBroadphasePairArray* pairArray = &UnmanagedPointer->getOverlappingPairArray();
	ReturnCachedObjectGcnew(AlignedBroadphasePairArray, _overlappingPairArray, pairArray);
}

btOverlappingPairCache* OverlappingPairCache::UnmanagedPointer::get()
{
	return (btOverlappingPairCache*)OverlappingPairCallback::UnmanagedPointer;
}


HashedOverlappingPairCache::HashedOverlappingPairCache(btHashedOverlappingPairCache* pairCache)
: OverlappingPairCache(pairCache)
{
}

HashedOverlappingPairCache::HashedOverlappingPairCache()
: OverlappingPairCache(new btHashedOverlappingPairCache)
{
}

bool HashedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return UnmanagedPointer->needsBroadphaseCollision(proxy0->_unmanaged, proxy1->_unmanaged);
}

int HashedOverlappingPairCache::Count::get()
{
	return UnmanagedPointer->GetCount();
}

OverlapFilterCallback^ HashedOverlappingPairCache::OverlapFilterCallback::get()
{
	return BulletSharp::OverlapFilterCallback::GetManaged(UnmanagedPointer->getOverlapFilterCallback());
}
void HashedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	UnmanagedPointer->setOverlapFilterCallback(value->UnmanagedPointer);
}

btHashedOverlappingPairCache* HashedOverlappingPairCache::UnmanagedPointer::get()
{
	return (btHashedOverlappingPairCache*)OverlappingPairCache::UnmanagedPointer;
}


SortedOverlappingPairCache::SortedOverlappingPairCache(btSortedOverlappingPairCache* sortedPairCache)
: OverlappingPairCache(sortedPairCache)
{
}

SortedOverlappingPairCache::SortedOverlappingPairCache()
: OverlappingPairCache(new btSortedOverlappingPairCache)
{
}

bool SortedOverlappingPairCache::NeedsBroadphaseCollision(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return UnmanagedPointer->needsBroadphaseCollision(proxy0->_unmanaged, proxy1->_unmanaged);
}

OverlapFilterCallback^ SortedOverlappingPairCache::OverlapFilterCallback::get()
{
	return BulletSharp::OverlapFilterCallback::GetManaged(UnmanagedPointer->getOverlapFilterCallback());
}
void SortedOverlappingPairCache::OverlapFilterCallback::set(BulletSharp::OverlapFilterCallback^ value)
{
	UnmanagedPointer->setOverlapFilterCallback(value->UnmanagedPointer);
}

btSortedOverlappingPairCache* SortedOverlappingPairCache::UnmanagedPointer::get()
{
	return (btSortedOverlappingPairCache*)OverlappingPairCache::UnmanagedPointer;
}


NullPairCache::NullPairCache(btNullPairCache* nullPairCache)
: OverlappingPairCache(nullPairCache)
{
}

NullPairCache::NullPairCache()
: OverlappingPairCache(new btNullPairCache)
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
