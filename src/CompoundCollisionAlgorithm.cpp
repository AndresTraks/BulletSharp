#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CompoundCollisionAlgorithm.h"
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
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: ActivatingCollisionAlgorithm(new btCompoundCollisionAlgorithm(*ci->UnmanagedPointer,
	body0Wrap->_unmanaged, body1Wrap->_unmanaged, isSwapped))
{
}

#endif
