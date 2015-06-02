#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObjectWrapper.h"
#include "CompoundCompoundCollisionAlgorithm.h"

CompoundCompoundCollisionAlgorithm::CreateFunc::CreateFunc(btCompoundCompoundCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

CompoundCompoundCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btCompoundCompoundCollisionAlgorithm::CreateFunc(), false)
{
}


CompoundCompoundCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc(btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

CompoundCompoundCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
	: CollisionAlgorithmCreateFunc(new btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc(), false)
{
}


CompoundCompoundCollisionAlgorithm::CompoundCompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
	: CompoundCollisionAlgorithm(new btCompoundCompoundCollisionAlgorithm(*ci->_native,
		body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

#endif
