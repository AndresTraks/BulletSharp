#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "BoxBoxCollisionAlgorithm.h"
#include "CollisionObject.h"
#include "PersistentManifold.h"

BoxBoxCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btBoxBoxCollisionAlgorithm::CreateFunc())
{
}

BoxBoxCollisionAlgorithm::BoxBoxCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: ActivatingCollisionAlgorithm(new btBoxBoxCollisionAlgorithm(*ci->UnmanagedPointer))
{
}

BoxBoxCollisionAlgorithm::BoxBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1)
: ActivatingCollisionAlgorithm(new btBoxBoxCollisionAlgorithm((mf != nullptr) ? mf->UnmanagedPointer : 0, *ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer))
{
}

#endif
