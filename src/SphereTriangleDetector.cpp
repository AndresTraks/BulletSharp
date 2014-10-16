#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "SphereShape.h"
#include "SphereTriangleDetector.h"
#include "TriangleShape.h"

#define Native static_cast<::SphereTriangleDetector*>(_native)

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(::SphereTriangleDetector* native)
	: DiscreteCollisionDetectorInterface(native)
{
}

BulletSharp::SphereTriangleDetector::SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle,
	btScalar contactBreakingThreshold)
	: DiscreteCollisionDetectorInterface(ALIGNED_NEW(::SphereTriangleDetector)((btSphereShape*)sphere->_native,
		(btTriangleShape*)triangle->_native, contactBreakingThreshold))
{
}

bool BulletSharp::SphereTriangleDetector::Collide(Vector3 sphereCenter, Vector3% point, Vector3% resultNormal,
	btScalar% depth, btScalar% timeOfImpact, btScalar contactBreakingThreshold)
{
	VECTOR3_CONV(sphereCenter);
	btVector3* pointTemp = ALIGNED_NEW(btVector3);
	btVector3* resultNormalTemp = ALIGNED_NEW(btVector3);
	btScalar depthTemp;
	btScalar timeOfImpactTemp;
	return Native->collide(VECTOR3_USE(sphereCenter), *pointTemp, *resultNormalTemp,
		depthTemp, timeOfImpactTemp, contactBreakingThreshold);
	depth = depthTemp;
	timeOfImpact = timeOfImpactTemp;
	VECTOR3_DEL(sphereCenter);
	ALIGNED_FREE(pointTemp);
	ALIGNED_FREE(resultNormalTemp);
}

#endif
