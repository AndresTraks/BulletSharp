#include "StdAfx.h"

#include "ConcaveShape.h"
#include "TriangleCallback.h"

#define Unmanaged (static_cast<btConcaveShape*>(_unmanaged))

ConcaveShape::ConcaveShape(btConcaveShape* concaveShape)
: CollisionShape(concaveShape)
{
}

void ConcaveShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Unmanaged->processAllTriangles(callback->UnmanagedPointer, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}
