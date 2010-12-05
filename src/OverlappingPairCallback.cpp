#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCallback.h"

OverlappingPairCallback::OverlappingPairCallback(btOverlappingPairCallback* pairCallback)
{
	_pairCallback = pairCallback;
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

	_pairCallback = NULL;

	OnDisposed(this, nullptr);
}

BroadphasePair^ OverlappingPairCallback::AddOverlappingPair(
	BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return gcnew BroadphasePair(_pairCallback->addOverlappingPair(
		proxy0->UnmanagedPointer, proxy1->UnmanagedPointer));
}

IntPtr OverlappingPairCallback::RemoveOverlappingPair(BroadphaseProxy^ proxy0,
	BroadphaseProxy^ proxy1, Dispatcher^ dispatcher)
{
	return IntPtr(_pairCallback->removeOverlappingPair(proxy0->UnmanagedPointer,
		proxy1->UnmanagedPointer, dispatcher->UnmanagedPointer));
}

void OverlappingPairCallback::RemoveOverlappingPairsContainingProxy(
	BroadphaseProxy^ proxy0, Dispatcher^ dispatcher)
{
	_pairCallback->removeOverlappingPairsContainingProxy(
		proxy0->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

bool OverlappingPairCallback::IsDisposed::get()
{
	return (_pairCallback == NULL);
}

btOverlappingPairCallback* OverlappingPairCallback::UnmanagedPointer::get()
{
	return _pairCallback;
}
void OverlappingPairCallback::UnmanagedPointer::set(btOverlappingPairCallback* value)
{
	_pairCallback = value;
}