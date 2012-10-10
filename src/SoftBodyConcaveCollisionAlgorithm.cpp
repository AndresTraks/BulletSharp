#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "SoftBodyConcaveCollisionAlgorithm.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"

SoftBodyConcaveCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSoftBodyConcaveCollisionAlgorithm::CreateFunc())
{
}


SoftBodyConcaveCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
: CollisionAlgorithmCreateFunc(new btSoftBodyConcaveCollisionAlgorithm::SwappedCreateFunc())
{
}


#define Native static_cast<btSoftBodyConcaveCollisionAlgorithm*>(_native)

SoftBodyConcaveCollisionAlgorithm::SoftBodyConcaveCollisionAlgorithm(btSoftBodyConcaveCollisionAlgorithm* algorithm)
: CollisionAlgorithm(algorithm)
{
}

SoftBodyConcaveCollisionAlgorithm::SoftBodyConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: CollisionAlgorithm(new btSoftBodyConcaveCollisionAlgorithm(*ci->_native, body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

void SoftBodyConcaveCollisionAlgorithm::ClearCache()
{
	Native->clearCache();
}

#endif
#endif
