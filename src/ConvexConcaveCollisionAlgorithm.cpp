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

ConvexConcaveCollisionAlgorithm::ConvexConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: ActivatingCollisionAlgorithm(new btConvexConcaveCollisionAlgorithm(*ci->UnmanagedPointer,
	body0Wrap->_unmanaged, body1Wrap->_unmanaged, isSwapped))
{
}

void ConvexConcaveCollisionAlgorithm::ClearCache()
{
	UnmanagedPointer->clearCache();
}

btConvexConcaveCollisionAlgorithm* ConvexConcaveCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btConvexConcaveCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
