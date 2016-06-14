#include "StdAfx.h"

#include "ConeShape.h"

#define Native static_cast<btConeShape*>(_native)

ConeShape::ConeShape(btConeShape* native)
	: ConvexInternalShape(native)
{
}

ConeShape::ConeShape(btScalar radius, btScalar height)
	: ConvexInternalShape(new btConeShape(radius, height))
{
}

int ConeShape::ConeUpIndex::get()
{
	return Native->getConeUpIndex();
}
void ConeShape::ConeUpIndex::set(int upIndex)
{
	Native->setConeUpIndex(upIndex);
}

btScalar ConeShape::Height::get()
{
	return Native->getHeight();
}
void ConeShape::Height::set(btScalar height)
{
	Native->setHeight(height);
}

btScalar ConeShape::Radius::get()
{
	return Native->getRadius();
}
void ConeShape::Radius::set(btScalar radius)
{
	Native->setRadius(radius);
}


ConeShapeX::ConeShapeX(btScalar radius, btScalar height)
	: ConeShape(new btConeShapeX(radius, height))
{
}


ConeShapeZ::ConeShapeZ(btScalar radius, btScalar height)
	: ConeShape(new btConeShapeZ(radius, height))
{
}
