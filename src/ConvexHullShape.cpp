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
	btVector3* pointTemp = new btVector3;

	for each (Vector3 point in points)
	{
		Math::Vector3ToBtVector3(point, pointTemp);
		UnmanagedPointer->addPoint(*pointTemp);
	}

	delete pointTemp;
}

void ConvexHullShape::AddPoint(Vector3 point)
{
	btVector3* pointTemp = Math::Vector3ToBtVector3(point);
	UnmanagedPointer->addPoint(*pointTemp);
	delete pointTemp;
}

#pragma managed(push, off)
void ConvexHullShape_GetScaledPoint(btConvexHullShape* shape, int i, btVector3* point)
{
	*point = shape->getScaledPoint(i);
}
#pragma managed(pop)
Vector3 ConvexHullShape::GetScaledPoint(int i)
{
	btVector3* pointTemp = new btVector3;
	ConvexHullShape_GetScaledPoint(UnmanagedPointer, i, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	delete pointTemp;
	return point;
}

int ConvexHullShape::NumPoints::get()
{
	return UnmanagedPointer->getNumPoints();
}

btConvexHullShape* ConvexHullShape::UnmanagedPointer::get()
{
	return (btConvexHullShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
