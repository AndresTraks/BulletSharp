#include "StdAfx.h"

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
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_pairCallback = NULL;
	
	OnDisposed( this, nullptr );
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