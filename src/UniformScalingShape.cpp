#include "StdAfx.h"

#include "UniformScalingShape.h"

UniformScalingShape::UniformScalingShape(btUniformScalingShape* shape)
: ConvexShape(shape)
{
}

UniformScalingShape::UniformScalingShape(ConvexShape^ convexChildShape, btScalar uniformScalingFactor)
: ConvexShape(new btUniformScalingShape(convexChildShape->UnmanagedPointer, uniformScalingFactor))
{
}

ConvexShape^ UniformScalingShape::ChildShape::get()
{
	btConvexShape* childShape = UnmanagedPointer->getChildShape();
	ReturnCachedObject(ConvexShape, _childShape, childShape);
}

btScalar UniformScalingShape::UniformScalingFactor::get()
{
	return UnmanagedPointer->getUniformScalingFactor();
}

btUniformScalingShape* UniformScalingShape::UnmanagedPointer::get()
{
	return (btUniformScalingShape*)ConvexShape::UnmanagedPointer;
}
