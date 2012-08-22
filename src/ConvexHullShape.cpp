#include "StdAfx.h"

#include "Collections.h"
#include "ConvexHullShape.h"

#define Unmanaged static_cast<btConvexHullShape*>(_unmanaged)

ConvexHullShape::ConvexHullShape()
: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
}

ConvexHullShape::ConvexHullShape(btConvexHullShape* shape)
: PolyhedralConvexAabbCachingShape(shape)
{
}

ConvexHullShape::ConvexHullShape(System::Collections::Generic::IEnumerable<Vector3>^ points)
: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
	btVector3* pointTemp = new btVector3;

	for each (Vector3 point in points)
	{
		Math::Vector3ToBtVector3(point, pointTemp);
		Unmanaged->addPoint(*pointTemp);
	}

	delete pointTemp;
}

void ConvexHullShape::AddPoint(Vector3 point)
{
	VECTOR3_DEF(point);
	Unmanaged->addPoint(VECTOR3_USE(point));
	VECTOR3_DEL(point);
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
	ConvexHullShape_GetScaledPoint(Unmanaged, i, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	delete pointTemp;
	return point;
}

int ConvexHullShape::NumPoints::get()
{
	return Unmanaged->getNumPoints();
}

Vector3Array^ ConvexHullShape::UnscaledPoints::get()
{
	btVector3* unscaledPoints = Unmanaged->getUnscaledPoints();
	int numPoints = Unmanaged->getNumPoints();

	if (_unscaledPoints == nullptr)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);
	else if (_unscaledPoints->Count != numPoints)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);

	return _unscaledPoints;
}
