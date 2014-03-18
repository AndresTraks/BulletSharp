#include "StdAfx.h"

#ifndef DISABLE_GIMPACT
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionDispatcher.h"
#include "GImpactCollisionAlgorithm.h"

GImpactCollisionAlgorithm::CreateFunc::CreateFunc(btGImpactCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native)
{
}

GImpactCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btGImpactCollisionAlgorithm::CreateFunc())
{
}

GImpactCollisionAlgorithm::GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* native)
	: ActivatingCollisionAlgorithm(native)
{
}

void GImpactCollisionAlgorithm::RegisterAlgorithm(CollisionDispatcher^ dispatcher)
{
	btGImpactCollisionAlgorithm::registerAlgorithm((btCollisionDispatcher*)dispatcher->_native);
}

#endif
#endif
