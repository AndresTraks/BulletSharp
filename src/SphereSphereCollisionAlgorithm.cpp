#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#pragma managed(pop)

#include "CollisionObject.h"
#include "PersistentManifold.h"
#include "SphereSphereCollisionAlgorithm.h"

SphereSphereCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSphereSphereCollisionAlgorithm::CreateFunc())
{
}

SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1)
: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer))
{
}

SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm(*ci->UnmanagedPointer))
{
}

btSphereSphereCollisionAlgorithm* SphereSphereCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereSphereCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
