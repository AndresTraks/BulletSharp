#include "StdAfx.h"

#include "SphereShape.h"

#define Native static_cast<btSphereShape*>(_native)

SphereShape::SphereShape(btScalar radius)
	: ConvexInternalShape(new btSphereShape(radius))
{
}

void SphereShape::SetUnscaledRadius(btScalar radius)
{
	Native->setUnscaledRadius(radius);
}

btScalar SphereShape::Radius::get()
{
	return Native->getRadius();
}
