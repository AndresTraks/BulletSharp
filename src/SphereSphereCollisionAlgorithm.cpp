#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"
#include "SphereSphereCollisionAlgorithm.h"

SphereSphereCollisionAlgorithm::CreateFunc::CreateFunc(btSphereSphereCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

SphereSphereCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btSphereSphereCollisionAlgorithm::CreateFunc(), false)
{
}


SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(PersistentManifold mf,
	CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ col0Wrap, CollisionObjectWrapper^ col1Wrap)
	: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm(mf._native,
		*ci->_native, col0Wrap->_native, col1Wrap->_native))
{
}

SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm(*ci->_native))
{
}

#endif
