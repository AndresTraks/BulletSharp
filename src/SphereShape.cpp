#include "StdAfx.h"

#include "SphereShape.h"

#define Unmanaged static_cast<btSphereShape*>(_unmanaged)

SphereShape::SphereShape(btSphereShape* shape)
: ConvexInternalShape(shape)
{
}

SphereShape::SphereShape(btScalar radius)
: ConvexInternalShape(new btSphereShape(radius))
{
}

void SphereShape::SetUnscaledRadius(btScalar radius)
{
	Unmanaged->setUnscaledRadius(radius);
}

btScalar SphereShape::Radius::get()
{
	return Unmanaged->getRadius();
}
