#include "StdAfx.h"

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionWorld.h"
#include "DiscreteDynamicsWorld.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#ifndef DISABLE_UNCOMMON
#include "SimulationIslandManager.h"
#endif
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#include "ConstraintSolver.h"
#endif

#define Unmanaged static_cast<btDiscreteDynamicsWorld*>(_unmanaged)

DiscreteDynamicsWorld::DiscreteDynamicsWorld(btDiscreteDynamicsWorld* world)
: DynamicsWorld(world)
{
}

DiscreteDynamicsWorld::DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache,
	#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
	#endif
	CollisionConfiguration^ collisionConfiguration)
: DynamicsWorld(new btDiscreteDynamicsWorld(dispatcher->UnmanagedPointer,
	pairCache->UnmanagedPointer,
	#ifndef DISABLE_CONSTRAINTS
	GetUnmanagedNullable(constraintSolver),
	#else
	0,
	#endif
	collisionConfiguration->UnmanagedPointer))
{
	_collisionConfiguration = collisionConfiguration;
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void DiscreteDynamicsWorld::ApplyGravity()
{
	Unmanaged->applyGravity();
}

#if !defined(DISABLE_CONSTRAINTS) && !defined (DISABLE_DEBUGDRAW)
void DiscreteDynamicsWorld::DebugDrawConstraint(TypedConstraint^ constraint)
{
	Unmanaged->debugDrawConstraint(constraint->UnmanagedPointer);
}
#endif

CollisionWorld^ DiscreteDynamicsWorld::CollisionWorld::get()
{
	return gcnew BulletSharp::CollisionWorld(Unmanaged->getCollisionWorld());
}

#ifndef DISABLE_UNCOMMON
SimulationIslandManager^ DiscreteDynamicsWorld::SimulationIslandManager::get()
{
	return gcnew BulletSharp::SimulationIslandManager(Unmanaged->getSimulationIslandManager());
}
#endif

void DiscreteDynamicsWorld::SetNumTasks (int numTasks)
{
	Unmanaged->setNumTasks(numTasks);
}

bool DiscreteDynamicsWorld::SynchronizeAllMotionStates::get()
{
	return Unmanaged->getSynchronizeAllMotionStates();
}
void DiscreteDynamicsWorld::SynchronizeAllMotionStates::set(bool value)
{
	return Unmanaged->setSynchronizeAllMotionStates(value);
}

void DiscreteDynamicsWorld::SynchronizeSingleMotionState(RigidBody^ body)
{
	Unmanaged->synchronizeSingleMotionState((btRigidBody*)body->_unmanaged);
}
