#include "StdAfx.h"

#include "QuantizedBvh.h"

QuantizedBvh::QuantizedBvh(btQuantizedBvh* bvh)
{
	_bvh = bvh;
}

QuantizedBvh::QuantizedBvh()
{
	_bvh = new btQuantizedBvh();
}

QuantizedBvh::~QuantizedBvh()
{
	this->!QuantizedBvh();
}

QuantizedBvh::!QuantizedBvh()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_bvh = NULL;
	
	OnDisposed( this, nullptr );
}

bool QuantizedBvh::IsDisposed::get()
{
	return (_bvh == NULL);
}

btQuantizedBvh* QuantizedBvh::UnmanagedPointer::get()
{
	return _bvh;
}
void QuantizedBvh::UnmanagedPointer::set(btQuantizedBvh* value)
{
	_bvh = value;
}
