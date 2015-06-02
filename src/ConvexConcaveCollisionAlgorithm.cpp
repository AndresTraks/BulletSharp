#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ConvexConcaveCollisionAlgorithm.h"

ConvexConcaveCollisionAlgorithm::CreateFunc::CreateFunc(btConvexConcaveCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

ConvexConcaveCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btConvexConcaveCollisionAlgorithm::CreateFunc(), false)
{
}


ConvexConcaveCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc(btConvexConcaveCollisionAlgorithm::SwappedCreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

ConvexConcaveCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
	: CollisionAlgorithmCreateFunc(new btConvexConcaveCollisionAlgorithm::SwappedCreateFunc(), false)
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
