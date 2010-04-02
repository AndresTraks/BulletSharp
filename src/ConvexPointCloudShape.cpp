#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvexPointCloudShape.h>
#pragma managed(pop)

#include "ConvexPointCloudShape.h"

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
	btVector3* point = new btVector3;
	ConvexPointCloudShape_GetScaledPoint(UnmanagedPointer, i, point);
	return Math::BtVector3ToVector3(point);
}

void ConvexPointCloudShape::SetPoints(array<Vector3>^ points, bool computeAabb, Vector3 localScaling)
{
	btVector3* btPoints = new btVector3[points->Length];
	int i;
	for (i=0; i<points->Length; i++)
		Math::Vector3ToBtVector3(points[i], &btPoints[i]);
	UnmanagedPointer->setPoints(btPoints, points->Length, computeAabb, *Math::Vector3ToBtVector3(localScaling));
}
/*
void ConvexPointCloudShape::SetPoints(array<Vector3>^ points, bool computeAabb)
{
	btVector3* btPoints = new btVector3[points->Length];
	int i;
	for (i=0; i<points->Length; i++)
		Math::Vector3ToBtVector3(points[i], &btPoints[i]);
	UnmanagedPointer->setPoints(btPoints, points->Length, computeAabb);
}

void ConvexPointCloudShape::SetPoints(array<Vector3>^ points)
{
	btVector3* btPoints = new btVector3[points->Length];
	int i;
	for (i=0; i<points->Length; i++)
		Math::Vector3ToBtVector3(points[i], &btPoints[i]);
	UnmanagedPointer->setPoints(btPoints, points->Length);
}
*/
int ConvexPointCloudShape::NumPoints::get()
{
	return UnmanagedPointer->getNumPoints();
}

btConvexPointCloudShape* ConvexPointCloudShape::UnmanagedPointer::get()
{
	return (btConvexPointCloudShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
