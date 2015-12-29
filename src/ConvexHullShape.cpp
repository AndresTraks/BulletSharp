#include "StdAfx.h"

#include "Collections.h"
#include "ConvexHullShape.h"

#define Native static_cast<btConvexHullShape*>(_native)

ConvexHullShape::ConvexHullShape(IEnumerable<Vector3>^ points)
	: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
	btVector3* pointTemp = ALIGNED_NEW(btVector3);

	for each (Vector3 point in points)
	{
		Math::Vector3ToBtVector3(point, pointTemp);
		Native->addPoint(*pointTemp);
	}
	Native->recalcLocalAabb();

	ALIGNED_FREE(pointTemp);
}

ConvexHullShape::ConvexHullShape()
	: PolyhedralConvexAabbCachingShape(new btConvexHullShape())
{
}

void ConvexHullShape::AddPoint(Vector3 point, bool recalculateLocalAabb)
{
	VECTOR3_CONV(point);
	Native->addPoint(VECTOR3_USE(point), recalculateLocalAabb);
	VECTOR3_DEL(point);
}

void ConvexHullShape::AddPoint(Vector3 point)
{
	VECTOR3_CONV(point);
	Native->addPoint(VECTOR3_USE(point));
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
	btVector3* pointTemp = ALIGNED_NEW(btVector3);
	ConvexHullShape_GetScaledPoint(Native, i, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	ALIGNED_FREE(pointTemp);
	return point;
}

void ConvexHullShape::Project(Matrix trans, Vector3 dir, btScalar% minProj, btScalar% maxProj,
	Vector3% witnesPtMin, Vector3% witnesPtMax)
{
	TRANSFORM_CONV(trans);
	VECTOR3_CONV(dir);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = ALIGNED_NEW(btVector3);
	btVector3* witnesPtMaxTemp = ALIGNED_NEW(btVector3);
	Native->project(TRANSFORM_USE(trans), VECTOR3_USE(dir), minProjTemp, maxProjTemp,
		*witnesPtMinTemp, *witnesPtMaxTemp);
	minProj = minProjTemp;
	maxProj = maxProjTemp;
	Math::BtVector3ToVector3(witnesPtMinTemp, witnesPtMin);
	Math::BtVector3ToVector3(witnesPtMaxTemp, witnesPtMax);
	TRANSFORM_DEL(trans);
	VECTOR3_DEL(dir);
	ALIGNED_FREE(witnesPtMinTemp);
	ALIGNED_FREE(witnesPtMaxTemp);
}

int ConvexHullShape::NumPoints::get()
{
	return Native->getNumPoints();
}

Vector3Array^ ConvexHullShape::UnscaledPoints::get()
{
	btVector3* unscaledPoints = Native->getUnscaledPoints();
	int numPoints = Native->getNumPoints();

	if (_unscaledPoints == nullptr)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);
	else if (_unscaledPoints->Count != numPoints)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);

	return _unscaledPoints;
}
