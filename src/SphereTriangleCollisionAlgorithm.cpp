#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h>
#pragma managed(pop)

#include "CollisionObject.h"
#include "PersistentManifold.h"
#include "SphereTriangleCollisionAlgorithm.h"

SphereTriangleCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSphereTriangleCollisionAlgorithm::CreateFunc())
{
}

SphereTriangleCollisionAlgorithm::SphereTriangleCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1, bool isSwapped)
: ActivatingCollisionAlgorithm(new btSphereTriangleCollisionAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer, isSwapped))
{
}

SphereTriangleCollisionAlgorithm::SphereTriangleCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: ActivatingCollisionAlgorithm(new btSphereTriangleCollisionAlgorithm(*ci->UnmanagedPointer))
{
}

btSphereTriangleCollisionAlgorithm* SphereTriangleCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereTriangleCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
