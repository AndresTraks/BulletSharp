#include "StdAfx.h"

#include "CapsuleShape.h"

#define Unmanaged static_cast<btCapsuleShape*>(_unmanaged)

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
	return Unmanaged->getHalfHeight();
}

btScalar CapsuleShape::Radius::get()
{
	return Unmanaged->getRadius();
}

int CapsuleShape::UpAxis::get()
{
	return Unmanaged->getUpAxis();
}


CapsuleShapeX::CapsuleShapeX(btScalar radius, btScalar height)
: CapsuleShape(new btCapsuleShapeX(radius, height))
{
}

CapsuleShapeZ::CapsuleShapeZ(btScalar radius, btScalar height)
: CapsuleShape(new btCapsuleShapeZ(radius, height))
{
}
