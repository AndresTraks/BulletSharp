#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObjectWrapper.h"
#include "CompoundCompoundCollisionAlgorithm.h"

CompoundCompoundCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btCompoundCompoundCollisionAlgorithm::CreateFunc())
{
}


CompoundCompoundCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
	: CollisionAlgorithmCreateFunc(new btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc())
{
}


CompoundCompoundCollisionAlgorithm::CompoundCompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
	: CompoundCollisionAlgorithm(new btCompoundCompoundCollisionAlgorithm(*ci->_native,
		body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

#endif
