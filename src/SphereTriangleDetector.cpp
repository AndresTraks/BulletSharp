#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "SphereTriangleDetector.h"
#include "SphereShape.h"
#include "TriangleShape.h"

#define Native static_cast<::SphereTriangleDetector*>(_native)

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(::SphereTriangleDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle, btScalar contactBreakingThreshold)
: DiscreteCollisionDetectorInterface(0)
{
	_native = ALIGNED_ALLOC(::SphereTriangleDetector);
	new (_native) ::SphereTriangleDetector(
		(btSphereShape*)sphere->_native, (btTriangleShape*)triangle->_native, contactBreakingThreshold);
}

#endif
