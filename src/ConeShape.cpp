#include "StdAfx.h"

#include "ConeShape.h"

ConeShape::ConeShape(btConeShape* shape)
: ConvexInternalShape(shape)
{
}

ConeShape::ConeShape(btScalar radius, btScalar height)
: ConvexInternalShape(new btConeShape(radius, height))
{
}

int ConeShape::ConeUpIndex::get()
{
	return UnmanagedPointer->getConeUpIndex();
}
void ConeShape::ConeUpIndex::set(int value)
{
	UnmanagedPointer->setConeUpIndex(value);
}

btScalar ConeShape::Height::get()
{
	return UnmanagedPointer->getHeight();
}

btScalar ConeShape::Radius::get()
{
	return UnmanagedPointer->getRadius();
}

btConeShape* ConeShape::UnmanagedPointer::get()
{
	return (btConeShape*)ConvexInternalShape::UnmanagedPointer;
}


ConeShapeX::ConeShapeX(btScalar radius, btScalar height)
: ConeShape(new btConeShapeX(radius, height))
{
}

ConeShapeZ::ConeShapeZ(btScalar radius, btScalar height)
: ConeShape(new btConeShapeX(radius, height))
{
}
