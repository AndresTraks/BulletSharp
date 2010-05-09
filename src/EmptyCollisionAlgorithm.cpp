#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h>
#pragma managed(pop)

#include "CollisionObject.h"
#include "EmptyCollisionAlgorithm.h"

EmptyAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btEmptyAlgorithm::CreateFunc())
{
}

EmptyAlgorithm::EmptyAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: CollisionAlgorithm(new btEmptyAlgorithm(*ci->UnmanagedPointer))
{
}

#endif
