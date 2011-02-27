#include "StdAfx.h"

#include "TriangleInfoMap.h"

TriangleInfoMap::TriangleInfoMap()
{
	_triangleInfoMap = new btTriangleInfoMap();
}

btTriangleInfoMap* TriangleInfoMap::UnmanagedPointer::get()
{
	return _triangleInfoMap;
}
void TriangleInfoMap::UnmanagedPointer::set(btTriangleInfoMap* value)
{
	_triangleInfoMap = value;
}
