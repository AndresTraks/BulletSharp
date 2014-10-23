#include "StdAfx.h"

#include "UniformScalingShape.h"

#define Native static_cast<btUniformScalingShape*>(_native)

UniformScalingShape::UniformScalingShape(ConvexShape^ convexChildShape, btScalar uniformScalingFactor)
	: ConvexShape(new btUniformScalingShape((btConvexShape*)convexChildShape->_native,
		uniformScalingFactor))
{
	_childShape = convexChildShape;
}

ConvexShape^ UniformScalingShape::ChildShape::get()
{
	return _childShape;
}

btScalar UniformScalingShape::UniformScalingFactor::get()
{
	return Native->getUniformScalingFactor();
}
