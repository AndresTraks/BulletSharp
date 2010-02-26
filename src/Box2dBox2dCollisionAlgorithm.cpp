#include "StdAfx.h"

#include "Box2dBox2dCollisionAlgorithm.h"

Box2dBox2dCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btBox2dBox2dCollisionAlgorithm::CreateFunc())
{
}
