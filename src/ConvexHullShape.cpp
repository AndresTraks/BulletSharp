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
		UnmanagedPointer->addPoint(*Math::Vector3ToBtVec3(point));
	}
}

btConvexHullShape* ConvexHullShape::UnmanagedPointer::get()
{
	return (btConvexHullShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
