#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "Box2DBox2DCollisionAlgorithm.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"

Box2DBox2DCollisionAlgorithm::CreateFunc::CreateFunc(btBox2dBox2dCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

Box2DBox2DCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btBox2dBox2dCollisionAlgorithm::CreateFunc(), false)
{
}


Box2DBox2DCollisionAlgorithm::Box2DBox2DCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: ActivatingCollisionAlgorithm(new btBox2dBox2dCollisionAlgorithm(*ci->_native))
{
}

Box2DBox2DCollisionAlgorithm::Box2DBox2DCollisionAlgorithm(PersistentManifold mf,
	CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
	: ActivatingCollisionAlgorithm(new btBox2dBox2dCollisionAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native))
{
}

#endif
