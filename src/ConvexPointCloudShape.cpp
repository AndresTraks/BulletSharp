#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Collections.h"
#include "ConvexPointCloudShape.h"

ConvexPointCloudShape::ConvexPointCloudShape(btConvexPointCloudShape* shape)
: PolyhedralConvexAabbCachingShape(shape)
{
}

ConvexPointCloudShape::ConvexPointCloudShape()
: PolyhedralConvexAabbCachingShape(new btConvexPointCloudShape())
{
}

ConvexPointCloudShape::ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling, bool computeAabb)
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
	btVector3* pointTemp = new btVector3;
	ConvexPointCloudShape_GetScaledPoint(UnmanagedPointer, i, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	delete pointTemp;
	return point;
}

void ConvexPointCloudShape::SetPoints(array<Vector3>^ points, bool computeAabb, Vector3 localScaling)
{
	btVector3* btPoints = Math::Vector3ArrayToUnmanaged(points);
	VECTOR3_DEF(localScaling);
	
	UnmanagedPointer->setPoints(btPoints, points->Length, computeAabb, VECTOR3_USE(localScaling));

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
	
	ConvexPointCloudShape_SetPoints(UnmanagedPointer, btPoints, points->Length, computeAabb);
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
	
	ConvexPointCloudShape_SetPoints(UnmanagedPointer, btPoints, points->Length);
}

int ConvexPointCloudShape::NumPoints::get()
{
	return UnmanagedPointer->getNumPoints();
}

Vector3Array^ ConvexPointCloudShape::UnscaledPoints::get()
{
	btVector3* unscaledPoints = UnmanagedPointer->getUnscaledPoints();
	int numPoints = UnmanagedPointer->getNumPoints();

	if (_unscaledPoints == nullptr)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);
	else if (_unscaledPoints->Count != numPoints)
		_unscaledPoints = gcnew Vector3Array(unscaledPoints, numPoints);

	return _unscaledPoints;
}

btConvexPointCloudShape* ConvexPointCloudShape::UnmanagedPointer::get()
{
	return (btConvexPointCloudShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}

#endif
