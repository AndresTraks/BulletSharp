#include "StdAfx.h"

#include "SphereShape.h"

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
	UnmanagedPointer->setUnscaledRadius(radius);
}

btScalar SphereShape::Radius::get()
{
	return UnmanagedPointer->getRadius();
}

btSphereShape* SphereShape::UnmanagedPointer::get()
{
	return (btSphereShape*)ConvexInternalShape::UnmanagedPointer;
}
