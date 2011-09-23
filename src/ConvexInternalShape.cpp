#include "StdAfx.h"

#include "ConvexInternalShape.h"

using namespace BulletSharp;

ConvexInternalShape::ConvexInternalShape(btConvexInternalShape* convexInternalShape)
: BulletSharp::ConvexShape(convexInternalShape)
{
}

void ConvexInternalShape::SetSafeMargin(btScalar minDimension, btScalar defaultMarginMultiplier)
{
	UnmanagedPointer->setSafeMargin(minDimension, defaultMarginMultiplier);
}

void ConvexInternalShape::SetSafeMargin(btScalar minDimension)
{
	UnmanagedPointer->setSafeMargin(minDimension);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents, btScalar defaultMarginMultiplier)
{
	btVector3* halfExtentsTemp = Math::Vector3ToBtVector3(halfExtents);
	UnmanagedPointer->setSafeMargin(*halfExtentsTemp, defaultMarginMultiplier);
	delete halfExtentsTemp;
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents)
{
	btVector3* halfExtentsTemp = Math::Vector3ToBtVector3(halfExtents);
	UnmanagedPointer->setSafeMargin(*halfExtentsTemp);
	delete halfExtentsTemp;
}

Vector3 ConvexInternalShape::ImplicitShapeDimensions::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getImplicitShapeDimensions());
}
void ConvexInternalShape::ImplicitShapeDimensions::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setImplicitShapeDimensions(*valueTemp);
	delete valueTemp;
}

Vector3 ConvexInternalShape::LocalScalingNV::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLocalScalingNV());
}

btScalar ConvexInternalShape::MarginNV::get()
{
	return UnmanagedPointer->getMarginNV();
}

btConvexInternalShape* ConvexInternalShape::UnmanagedPointer::get()
{
	return (btConvexInternalShape*)ConvexShape::UnmanagedPointer;
}


ConvexInternalAabbCachingShape::ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape)
: BulletSharp::ConvexInternalShape(convexInternalAabbCachingShape)
{
}
