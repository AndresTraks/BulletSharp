#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ConvexConcaveCollisionAlgorithm.h"

ConvexConcaveCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btConvexConcaveCollisionAlgorithm::CreateFunc())
{
}


ConvexConcaveCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
	: CollisionAlgorithmCreateFunc(new btConvexConcaveCollisionAlgorithm::SwappedCreateFunc())
{
}


#define Native static_cast<btConvexConcaveCollisionAlgorithm*>(_native)

ConvexConcaveCollisionAlgorithm::ConvexConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
	: ActivatingCollisionAlgorithm(new btConvexConcaveCollisionAlgorithm(*ci->_native,
		body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

void ConvexConcaveCollisionAlgorithm::ClearCache()
{
	Native->clearCache();
}

#endif
