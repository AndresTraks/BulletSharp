#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h>
#pragma managed(pop)

#include "CollisionObject.h"
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
	CollisionObject^ body0, CollisionObject^ body1, bool isSwapped)
: ActivatingCollisionAlgorithm(new btConvexConcaveCollisionAlgorithm(*ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer, isSwapped))
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
