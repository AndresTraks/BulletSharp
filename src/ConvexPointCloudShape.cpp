#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Collections.h"
#include "ConvexPointCloudShape.h"

#define Native static_cast<btConvexPointCloudShape*>(_native)

ConvexPointCloudShape::ConvexPointCloudShape()
	: PolyhedralConvexAabbCachingShape(new btConvexPointCloudShape())
{
}

ConvexPointCloudShape::ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling,
	bool computeAabb)
	: PolyhedralConvexAabbCachingShape(new btConvexPointCloudShape())
{
	SetPoints(points, computeAabb, localScaling);
}

ConvexPointCloudShape::ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling)
	: PolyhedralConvexAabbCachingShape(new btConvexPointCloudShape())
{
	SetPoints(points, true, localScaling);
}

#pragma managed(push, off)
void ConvexPointCloudShape_GetScaledPoint(btConvexPointCloudShape* shape, int i, btVector3* point)
{
	*point = shape->getScaledPoint(i);
}
#pragma managed(pop)
Vector3 ConvexPointCloudShape::GetScaledPoint(int i)
{
	btVector3* pointTemp = ALIGNED_NEW(btVector3);
	ConvexPointCloudShape_GetScaledPoint(Native, i, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	ALIGNED_FREE(pointTemp);
	return point;
}

void ConvexPointCloudShape::SetPoints(array<Vector3>^ points, bool computeAabb,
	Vector3 localScaling)
{
	btVector3* btPoints = Math::Vector3ArrayToUnmanaged(points);
	VECTOR3_CONV(localScaling);
	Native->setPoints(btPoints, points->Length, computeAabb, VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
	// Don't delete btPoints, they'll be used by btConvexPointCloudShape.
}

#pragma managed(push, off)
void ConvexPointCloudShape_SetPoints(btConvexPointCloudShape* shape, btVector3* points, int numPoints, bool computeAabb)
{
	shape->setPoints(points, numPoints, computeAabb);
}
#pragma managed(pop)
void ConvexPointCloudShape::SetPoints(array<Vector3>^ points, bool computeAabb)
{
	btVector3* btPoints = Math::Vector3ArrayToUnmanaged(points);
	
	ConvexPointCloudShape_SetPoints(Native, btPoints, points->Length, computeAabb);
}

#pragma managed(push, off)
void ConvexPointCloudShape_SetPoints(btConvexPointCloudShape* shape, btVector3* points, int numPoints)
{
	shape->setPoints(points, numPoints);
}
#pragma managed(pop)
void ConvexPointCloudShape::SetPoints(array<Vector3>^ points)
{
	btVector3* btPoints = Math::Vector3ArrayToUnmanaged(points);
	
	ConvexPointCloudShape_SetPoints(Native, btPoints, points->Length);
}

int ConvexPointCloudShape::NumPoints::get()
{
	return Native->getNumPoints();
}

Vector3Array^ ConvexPointCloudShape::UnscaledPoints::get()
{
	btVector3* unscaledPoints = Native->getUnscaledPoints();
	int numPoints = Native->getNumPoints();

	if (_unscaledPoints == nullptr)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);
	else if (_unscaledPoints->Count != numPoints)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);

	return _unscaledPoints;
}

#endif
