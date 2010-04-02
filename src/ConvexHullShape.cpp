#include "StdAfx.h"

#include "ConvexHullShape.h"

ConvexHullShape::ConvexHullShape()
: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
}

ConvexHullShape::ConvexHullShape(btConvexHullShape* shape)
: PolyhedralConvexAabbCachingShape(shape)
{
}

ConvexHullShape::ConvexHullShape(array<Vector3>^ points)
: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
	for each (Vector3 point in points)
	{
		UnmanagedPointer->addPoint(*Math::Vector3ToBtVector3(point));
	}
}

void ConvexHullShape::AddPoint(Vector3 point)
{
	UnmanagedPointer->addPoint(*Math::Vector3ToBtVector3(point));
}

#pragma managed(push, off)
void ConvexHullShape_GetScaledPoint(btConvexHullShape* shape, int i, btVector3* point)
{
	*point = shape->getScaledPoint(i);
}
#pragma managed(pop)
Vector3 ConvexHullShape::GetScaledPoint(int i)
{
	btVector3* point = new btVector3;
	ConvexHullShape_GetScaledPoint(UnmanagedPointer, i, point);
	return Math::BtVector3ToVector3(point);
}

int ConvexHullShape::NumPoints::get()
{
	return UnmanagedPointer->getNumPoints();
}

btConvexHullShape* ConvexHullShape::UnmanagedPointer::get()
{
	return (btConvexHullShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
