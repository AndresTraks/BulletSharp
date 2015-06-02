#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "EmptyCollisionAlgorithm.h"

EmptyAlgorithm::CreateFunc::CreateFunc(btEmptyAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

EmptyAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btEmptyAlgorithm::CreateFunc(), false)
{
}


EmptyAlgorithm::EmptyAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: CollisionAlgorithm(new btEmptyAlgorithm(*ci->_native))
{
}

#endif
