#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "SphereTriangleDetector.h"
#include "SphereShape.h"
#include "TriangleShape.h"

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(::SphereTriangleDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle, btScalar contactBreakingThreshold)
: DiscreteCollisionDetectorInterface(new ::SphereTriangleDetector(
	(btSphereShape*)sphere->_unmanaged, (btTriangleShape*)triangle->_unmanaged, contactBreakingThreshold))
{
}

::SphereTriangleDetector* BulletSharp::SphereTriangleDetector::UnmanagedPointer::get()
{
	return (::SphereTriangleDetector*)DiscreteCollisionDetectorInterface::UnmanagedPointer;
}

#endif
