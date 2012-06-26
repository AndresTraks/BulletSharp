#include "StdAfx.h"

#include "ConcaveShape.h"
#include "TriangleCallback.h"

ConcaveShape::ConcaveShape(btConcaveShape* concaveShape)
: CollisionShape(concaveShape)
{
}

void ConcaveShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	UnmanagedPointer->processAllTriangles(callback->UnmanagedPointer, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

btConcaveShape* ConcaveShape::UnmanagedPointer::get()
{
	return (btConcaveShape*)CollisionShape::UnmanagedPointer;
}
