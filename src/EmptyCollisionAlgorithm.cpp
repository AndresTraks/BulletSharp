#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "EmptyCollisionAlgorithm.h"

EmptyAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btEmptyAlgorithm::CreateFunc())
{
}

EmptyAlgorithm::EmptyAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: CollisionAlgorithm(new btEmptyAlgorithm(*ci->_native))
{
}

#endif
