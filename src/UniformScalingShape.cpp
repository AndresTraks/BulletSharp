#include "StdAfx.h"

#include "UniformScalingShape.h"

#define Native static_cast<btUniformScalingShape*>(_native)

UniformScalingShape::UniformScalingShape(btUniformScalingShape* native)
	: ConvexShape(native)
{
}

UniformScalingShape::UniformScalingShape(ConvexShape^ convexChildShape, btScalar uniformScalingFactor)
	: ConvexShape(new btUniformScalingShape((btConvexShape*)convexChildShape->_native,
		uniformScalingFactor))
{
}

ConvexShape^ UniformScalingShape::ChildShape::get()
{
	return (ConvexShape^)CollisionShape::GetManaged(Native->getChildShape());
}

btScalar UniformScalingShape::UniformScalingFactor::get()
{
	return Native->getUniformScalingFactor();
}

