#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "SoftBodyConcaveCollisionAlgorithm.h"
#include "CollisionObject.h"

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
	CollisionObject^ body0, CollisionObject^ body1, bool isSwapped)
: CollisionAlgorithm(new btSoftBodyConcaveCollisionAlgorithm(*ci->UnmanagedPointer, body0->UnmanagedPointer, body1->UnmanagedPointer, isSwapped))
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
