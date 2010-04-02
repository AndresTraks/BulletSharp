#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h>
#pragma managed(pop)

#include "CompoundCollisionAlgorithm.h"
#include "CollisionObject.h"
#include "PersistentManifold.h"

CompoundCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btCompoundCollisionAlgorithm::CreateFunc())
{
}

CompoundCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
: CollisionAlgorithmCreateFunc(new btCompoundCollisionAlgorithm::SwappedCreateFunc())
{
}

CompoundCollisionAlgorithm::CompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1, bool isSwapped)
: ActivatingCollisionAlgorithm(new btCompoundCollisionAlgorithm(*ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer, isSwapped))
{
}

#endif
