#include "StdAfx.h"

#include "ConcaveShape.h"
#include "TriangleCallback.h"

ConcaveShape::ConcaveShape(btConcaveShape* concaveShape)
: CollisionShape(concaveShape)
{
}

void ConcaveShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	UnmanagedPointer->processAllTriangles(callback->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

btConcaveShape* ConcaveShape::UnmanagedPointer::get()
{
	return (btConcaveShape*)CollisionShape::UnmanagedPointer;
}
