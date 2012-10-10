#include "StdAfx.h"

#include "ConvexInternalShape.h"

#define Native static_cast<btConvexInternalShape*>(_native)

ConvexInternalShape::ConvexInternalShape(btConvexInternalShape* convexInternalShape)
: BulletSharp::ConvexShape(convexInternalShape)
{
}

void ConvexInternalShape::SetSafeMargin(btScalar minDimension, btScalar defaultMarginMultiplier)
{
	Native->setSafeMargin(minDimension, defaultMarginMultiplier);
}

void ConvexInternalShape::SetSafeMargin(btScalar minDimension)
{
	Native->setSafeMargin(minDimension);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents, btScalar defaultMarginMultiplier)
{
	VECTOR3_DEF(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents), defaultMarginMultiplier);
	VECTOR3_DEL(halfExtents);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents));
	VECTOR3_DEL(halfExtents);
}

Vector3 ConvexInternalShape::ImplicitShapeDimensions::get()
{
	return Math::BtVector3ToVector3(&Native->getImplicitShapeDimensions());
}
void ConvexInternalShape::ImplicitShapeDimensions::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setImplicitShapeDimensions(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Vector3 ConvexInternalShape::LocalScalingNV::get()
{
	return Math::BtVector3ToVector3(&Native->getLocalScalingNV());
}

btScalar ConvexInternalShape::MarginNV::get()
{
	return Native->getMarginNV();
}


ConvexInternalAabbCachingShape::ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape)
: BulletSharp::ConvexInternalShape(convexInternalAabbCachingShape)
{
}
