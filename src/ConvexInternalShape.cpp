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
	VECTOR3_DEF(halfExtents);
	UnmanagedPointer->setSafeMargin(VECTOR3_USE(halfExtents), defaultMarginMultiplier);
	VECTOR3_DEL(halfExtents);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	UnmanagedPointer->setSafeMargin(VECTOR3_USE(halfExtents));
	VECTOR3_DEL(halfExtents);
}

Vector3 ConvexInternalShape::ImplicitShapeDimensions::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getImplicitShapeDimensions());
}
void ConvexInternalShape::ImplicitShapeDimensions::set(Vector3 value)
{
	VECTOR3_DEF(value);
	UnmanagedPointer->setImplicitShapeDimensions(VECTOR3_USE(value));
	VECTOR3_DEL(value);
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
