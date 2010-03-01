#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h>
#pragma managed(pop)

#include "Box2dBox2dCollisionAlgorithm.h"

Box2dBox2dCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btBox2dBox2dCollisionAlgorithm::CreateFunc())
{
}
