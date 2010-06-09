#include "StdAfx.h"

#include "CapsuleShape.h"

CapsuleShape::CapsuleShape(btCapsuleShape* shape)
: ConvexInternalShape(shape)
{
}

CapsuleShape::CapsuleShape(btScalar radius, btScalar height)
: ConvexInternalShape(new btCapsuleShape(radius, height))
{
}

btScalar CapsuleShape::HalfHeight::get()
{
	return UnmanagedPointer->getHalfHeight();
}

btScalar CapsuleShape::Radius::get()
{
	return UnmanagedPointer->getRadius();
}

int CapsuleShape::UpAxis::get()
{
	return UnmanagedPointer->getUpAxis();
}

btCapsuleShape* CapsuleShape::UnmanagedPointer::get()
{
	return (btCapsuleShape*)ConvexInternalShape::UnmanagedPointer;
}


CapsuleShapeX::CapsuleShapeX(btScalar radius, btScalar height)
: CapsuleShape(new btCapsuleShapeX(radius, height))
{
}

CapsuleShapeZ::CapsuleShapeZ(btScalar radius, btScalar height)
: CapsuleShape(new btCapsuleShapeZ(radius, height))
{
}
