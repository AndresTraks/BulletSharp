#include "StdAfx.h"

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "DiscreteDynamicsWorld.h"
#include "Dispatcher.h"
#ifndef DISABLE_CONSTRAINTS
#include "ConstraintSolver.h"
#endif

DiscreteDynamicsWorld::DiscreteDynamicsWorld(btDiscreteDynamicsWorld* world)
: DynamicsWorld(world)
{
}

#ifndef DISABLE_CONSTRAINTS

DiscreteDynamicsWorld::DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache, ConstraintSolver^ constraintSolver,
	CollisionConfiguration^ collisionConfiguration)
: DynamicsWorld(new btDiscreteDynamicsWorld(dispatcher->UnmanagedPointer,
		pairCache->UnmanagedPointer,
		(constraintSolver != nullptr) ? constraintSolver->UnmanagedPointer : 0,
		collisionConfiguration->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

#else

DiscreteDynamicsWorld::DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache,	CollisionConfiguration^ collisionConfiguration)
: DynamicsWorld(new btDiscreteDynamicsWorld(dispatcher->UnmanagedPointer,
		pairCache->UnmanagedPointer, 0, collisionConfiguration->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

#endif

// Set gravity by components
void DiscreteDynamicsWorld::SetGravity(btScalar x, btScalar y, btScalar z)
{
	btVector3* gravity = new btVector3(x,y,z);
	UnmanagedPointer->setGravity(*gravity);
	delete gravity;
}

btDiscreteDynamicsWorld* DiscreteDynamicsWorld::UnmanagedPointer::get()
{
	return (btDiscreteDynamicsWorld*)DynamicsWorld::UnmanagedPointer;
}
