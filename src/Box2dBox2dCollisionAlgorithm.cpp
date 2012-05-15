#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "Box2dBox2dCollisionAlgorithm.h"
#include "CollisionObject.h"
#include "PersistentManifold.h"

Box2dBox2dCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btBox2dBox2dCollisionAlgorithm::CreateFunc())
{
}

Box2dBox2dCollisionAlgorithm::Box2dBox2dCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: ActivatingCollisionAlgorithm(new btBox2dBox2dCollisionAlgorithm(*ci->UnmanagedPointer))
{
}

Box2dBox2dCollisionAlgorithm::Box2dBox2dCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1)
: ActivatingCollisionAlgorithm(new btBox2dBox2dCollisionAlgorithm((mf != nullptr) ? mf->UnmanagedPointer : 0, *ci->UnmanagedPointer,
	body0->_unmanaged, body1->_unmanaged))
{
}

#endif
