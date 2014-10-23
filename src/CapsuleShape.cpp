#include "StdAfx.h"

#include "CapsuleShape.h"

#define Native static_cast<btCapsuleShape*>(_native)

CapsuleShape::CapsuleShape(btCapsuleShape* native)
	: ConvexInternalShape(native)
{
}

CapsuleShape::CapsuleShape(btScalar radius, btScalar height)
	: ConvexInternalShape(new btCapsuleShape(radius, height))
{
}

btScalar CapsuleShape::HalfHeight::get()
{
	return Native->getHalfHeight();
}

btScalar CapsuleShape::Radius::get()
{
	return Native->getRadius();
}

int CapsuleShape::UpAxis::get()
{
	return Native->getUpAxis();
}


CapsuleShapeX::CapsuleShapeX(btScalar radius, btScalar height)
	: CapsuleShape(new btCapsuleShapeX(radius, height))
{
}


CapsuleShapeZ::CapsuleShapeZ(btScalar radius, btScalar height)
	: CapsuleShape(new btCapsuleShapeZ(radius, height))
{
}
