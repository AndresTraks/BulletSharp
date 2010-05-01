#include "StdAfx.h"

#include "CollisionDispatcher.h"
#include "GImpactCollisionAlgorithm.h"

GImpactCollisionAlgorithm::GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* algorithm)
: ActivatingCollisionAlgorithm(algorithm)
{
}

void GImpactCollisionAlgorithm::RegisterAlgorithm(CollisionDispatcher^ dispatcher)
{
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher->UnmanagedPointer);
}
