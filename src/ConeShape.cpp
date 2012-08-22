#include "StdAfx.h"

#include "ConeShape.h"

#define Unmanaged static_cast<btConeShape*>(_unmanaged)

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
	return Unmanaged->getConeUpIndex();
}
void ConeShape::ConeUpIndex::set(int value)
{
	Unmanaged->setConeUpIndex(value);
}

btScalar ConeShape::Height::get()
{
	return Unmanaged->getHeight();
}

btScalar ConeShape::Radius::get()
{
	return Unmanaged->getRadius();
}


ConeShapeX::ConeShapeX(btScalar radius, btScalar height)
: ConeShape(new btConeShapeX(radius, height))
{
}

ConeShapeZ::ConeShapeZ(btScalar radius, btScalar height)
: ConeShape(new btConeShapeX(radius, height))
{
}
