#include "StdAfx.h"

#include "TriangleCallback.h"

TriangleCallback::TriangleCallback(btTriangleCallback* callback)
{
	_callback = callback;
}

TriangleCallback::~TriangleCallback()
{
	this->!TriangleCallback();
}

TriangleCallback::!TriangleCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

void TriangleCallback::ProcessTriangle(Vector3 triangle, int partId, int triangleIndex)
{
	btVector3* triangleTemp = Math::Vector3ToBtVector3(triangle);
	UnmanagedPointer->processTriangle(triangleTemp, partId, triangleIndex);
	delete triangleTemp;
}

bool TriangleCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btTriangleCallback* TriangleCallback::UnmanagedPointer::get()
{
	return _callback;
}
void TriangleCallback::UnmanagedPointer::set(btTriangleCallback* value)
{
	_callback = value;
}


InternalTriangleIndexCallback::InternalTriangleIndexCallback(btInternalTriangleIndexCallback* callback)
{
	_callback = callback;
}

InternalTriangleIndexCallback::~InternalTriangleIndexCallback()
{
	this->!InternalTriangleIndexCallback();
}

InternalTriangleIndexCallback::!InternalTriangleIndexCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

void InternalTriangleIndexCallback::InternalProcessTriangleIndex(Vector3 triangle, int partId, int triangleIndex)
{
	btVector3* triangleTemp = Math::Vector3ToBtVector3(triangle);
	UnmanagedPointer->internalProcessTriangleIndex(triangleTemp, partId, triangleIndex);
	delete triangleTemp;
}

bool InternalTriangleIndexCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btInternalTriangleIndexCallback* InternalTriangleIndexCallback::UnmanagedPointer::get()
{
	return _callback;
}
void InternalTriangleIndexCallback::UnmanagedPointer::set(btInternalTriangleIndexCallback* value)
{
	_callback = value;
}
