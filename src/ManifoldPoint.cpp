#include "StdAfx.h"

#include "ManifoldPoint.h"

ManifoldPoint::ManifoldPoint()
{
	_point = new btManifoldPoint();
}

btManifoldPoint* ManifoldPoint::UnmanagedPointer::get()
{
	return _point;
}
void ManifoldPoint::UnmanagedPointer::set(btManifoldPoint* value)
{
	_point = value;
}
