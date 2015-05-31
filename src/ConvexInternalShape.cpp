#include "StdAfx.h"

#include "ConvexInternalShape.h"

#define Native static_cast<btConvexInternalShape*>(_native)

ConvexInternalShape::ConvexInternalShape(btConvexInternalShape* native)
	: ConvexShape(native)
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

void ConvexInternalShape::SetSafeMarginRef(Vector3% halfExtents, btScalar defaultMarginMultiplier)
{
	VECTOR3_CONV(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents), defaultMarginMultiplier);
	VECTOR3_DEL(halfExtents);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents, btScalar defaultMarginMultiplier)
{
	VECTOR3_CONV(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents), defaultMarginMultiplier);
	VECTOR3_DEL(halfExtents);
}

void ConvexInternalShape::SetSafeMarginRef(Vector3% halfExtents)
{
	VECTOR3_CONV(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents));
	VECTOR3_DEL(halfExtents);
}

void ConvexInternalShape::SetSafeMargin(Vector3 halfExtents)
{
	VECTOR3_CONV(halfExtents);
	Native->setSafeMargin(VECTOR3_USE(halfExtents));
	VECTOR3_DEL(halfExtents);
}

Vector3 ConvexInternalShape::ImplicitShapeDimensions::get()
{
	return Math::BtVector3ToVector3(&Native->getImplicitShapeDimensions());
}
void ConvexInternalShape::ImplicitShapeDimensions::set(Vector3 dimensions)
{
	VECTOR3_CONV(dimensions);
	Native->setImplicitShapeDimensions(VECTOR3_USE(dimensions));
	VECTOR3_DEL(dimensions);
}

Vector3 ConvexInternalShape::LocalScalingNV::get()
{
	return Math::BtVector3ToVector3(&Native->getLocalScalingNV());
}

btScalar ConvexInternalShape::MarginNV::get()
{
	return Native->getMarginNV();
}


#undef Native
#define Native static_cast<btConvexInternalAabbCachingShape*>(_native)

ConvexInternalAabbCachingShape::ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* native)
	: ConvexInternalShape(native)
{
}

void ConvexInternalAabbCachingShape::RecalcLocalAabb()
{
	Native->recalcLocalAabb();
}
