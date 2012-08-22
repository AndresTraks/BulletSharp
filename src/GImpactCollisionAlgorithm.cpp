#include "StdAfx.h"

#ifndef DISABLE_GIMPACT
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionDispatcher.h"
#include "GImpactCollisionAlgorithm.h"

GImpactCollisionAlgorithm::GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* algorithm)
: ActivatingCollisionAlgorithm(algorithm)
{
}

void GImpactCollisionAlgorithm::RegisterAlgorithm(CollisionDispatcher^ dispatcher)
{
	btGImpactCollisionAlgorithm::registerAlgorithm((btCollisionDispatcher*)dispatcher->_unmanaged);
}

#endif
#endif
