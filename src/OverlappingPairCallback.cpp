#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "OverlappingPairCallback.h"
#ifndef DISABLE_UNCOMMON
#include "GhostObject.h"
#endif

OverlappingPairCallback::OverlappingPairCallback(btOverlappingPairCallback* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

OverlappingPairCallback::~OverlappingPairCallback()
{
	this->!OverlappingPairCallback();
}

OverlappingPairCallback::!OverlappingPairCallback()
{
	if (this->IsDisposed)
		return;

	if (!_preventDelete) {
		delete _native;
	}
	_native = NULL;
}

OverlappingPairCallback::OverlappingPairCallback()
{
	_native = new OverlappingPairCallbackWrapper(this);
}

bool OverlappingPairCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#define Callback static_cast<OverlappingPairCallback^>(VoidPtrToGCHandle(_overlappingPairCallback).Target)

OverlappingPairCallbackWrapper::OverlappingPairCallbackWrapper(OverlappingPairCallback^ overlappingPairCallback)
{
	_overlappingPairCallback = GCHandleToVoidPtr(GCHandle::Alloc(overlappingPairCallback, GCHandleType::Weak));
}

OverlappingPairCallbackWrapper::~OverlappingPairCallbackWrapper()
{
	VoidPtrToGCHandle(_overlappingPairCallback).Free();
}

btBroadphasePair* OverlappingPairCallbackWrapper::addOverlappingPair(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1)
{
	BroadphasePair^ pair = Callback->AddOverlappingPair(BroadphaseProxy::GetManaged(proxy0), BroadphaseProxy::GetManaged(proxy1));
	return GetUnmanagedNullable(pair);
}

void* OverlappingPairCallbackWrapper::removeOverlappingPair(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1, btDispatcher* dispatcher)
{
	Dispatcher^ dispatcherManaged = nullptr; // TODO
	return Callback->RemoveOverlappingPair(
		BroadphaseProxy::GetManaged(proxy0), BroadphaseProxy::GetManaged(proxy1), dispatcherManaged).ToPointer();
}

void OverlappingPairCallbackWrapper::removeOverlappingPairsContainingProxy(btBroadphaseProxy* proxy0, btDispatcher* dispatcher)
{
	Dispatcher^ dispatcherManaged = nullptr; // TODO
	Callback->RemoveOverlappingPairsContainingProxy(BroadphaseProxy::GetManaged(proxy0), dispatcherManaged);
}
