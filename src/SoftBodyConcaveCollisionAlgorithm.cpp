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


SoftBodyConcaveCollisionAlgorithm::SoftBodyConcaveCollisionAlgorithm(btSoftBodyConcaveCollisionAlgorithm* algorithm)
: CollisionAlgorithm(algorithm)
{
}

SoftBodyConcaveCollisionAlgorithm::SoftBodyConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: CollisionAlgorithm(new btSoftBodyConcaveCollisionAlgorithm(*ci->_unmanaged, body0Wrap->_unmanaged, body1Wrap->_unmanaged, isSwapped))
{
}

void SoftBodyConcaveCollisionAlgorithm::ClearCache()
{
	UnmanagedPointer->clearCache();
}

btSoftBodyConcaveCollisionAlgorithm* SoftBodyConcaveCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSoftBodyConcaveCollisionAlgorithm*) CollisionAlgorithm::UnmanagedPointer;
}

#endif
#endif
