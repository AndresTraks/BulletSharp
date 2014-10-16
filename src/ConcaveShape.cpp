#include "StdAfx.h"

#include "ConcaveShape.h"
#include "TriangleCallback.h"

#define Native static_cast<btConcaveShape*>(_native)

ConcaveShape::ConcaveShape(btConcaveShape* native)
	: CollisionShape(native)
{
}

void ConcaveShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin,
	Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->processAllTriangles(callback->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}
