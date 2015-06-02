#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "BoxBoxCollisionAlgorithm.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"

BoxBoxCollisionAlgorithm::CreateFunc::CreateFunc(btBoxBoxCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

BoxBoxCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btBoxBoxCollisionAlgorithm::CreateFunc(), false)
{
}


BoxBoxCollisionAlgorithm::BoxBoxCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: ActivatingCollisionAlgorithm(new btBoxBoxCollisionAlgorithm(*ci->_native))
{
}

BoxBoxCollisionAlgorithm::BoxBoxCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
	: ActivatingCollisionAlgorithm(new btBoxBoxCollisionAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native))
{
}

#endif
