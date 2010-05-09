#include "StdAfx.h"

#include "SphereTriangleDetector.h"
#include "SphereShape.h"
#include "TriangleShape.h"

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(::SphereTriangleDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle, btScalar contactBreakingThreshold)
: DiscreteCollisionDetectorInterface(new ::SphereTriangleDetector(
	sphere->UnmanagedPointer, triangle->UnmanagedPointer, contactBreakingThreshold))
{
}

::SphereTriangleDetector* BulletSharp::SphereTriangleDetector::UnmanagedPointer::get()
{
	return (::SphereTriangleDetector*)DiscreteCollisionDetectorInterface::UnmanagedPointer;
}
