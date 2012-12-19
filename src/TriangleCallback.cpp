#include "StdAfx.h"

#include "TriangleCallback.h"

TriangleCallback::TriangleCallback(btTriangleCallback* callback)
{
	_native = callback;
}

TriangleCallback::~TriangleCallback()
{
	this->!TriangleCallback();
}

TriangleCallback::!TriangleCallback()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	delete _native;
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

void TriangleCallback::ProcessTriangle(Vector3 triangle, int partId, int triangleIndex)
{
	VECTOR3_DEF(triangle);
	_native->processTriangle(VECTOR3_PTR(triangle), partId, triangleIndex);
	VECTOR3_DEL(triangle);
}

bool TriangleCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#ifndef DISABLE_INTERNAL
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
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	_callback = NULL;
	
	OnDisposed(this, nullptr);
}

// TODO: triangle is an array
void InternalTriangleIndexCallback::InternalProcessTriangleIndex(Vector3 triangle, int partId, int triangleIndex)
{
	VECTOR3_DEF(triangle);
	UnmanagedPointer->internalProcessTriangleIndex(VECTOR3_PTR(triangle), partId, triangleIndex);
	VECTOR3_DEL(triangle);
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
#endif
