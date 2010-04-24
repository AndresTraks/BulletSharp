#include "StdAfx.h"

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionWorld.h"
#include "DiscreteDynamicsWorld.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#include "SimulationIslandManager.h"
#include "TypedConstraint.h"
#ifndef DISABLE_CONSTRAINTS
#include "ConstraintSolver.h"
#endif

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
	(constraintSolver != nullptr) ? constraintSolver->UnmanagedPointer : 0,
	#else
	0,
	#endif
	collisionConfiguration->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void DiscreteDynamicsWorld::AddRigidBody(RigidBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask)
{
	UnmanagedPointer->addRigidBody(body->UnmanagedPointer, (short)group, (short)mask);
}

void DiscreteDynamicsWorld::ApplyGravity()
{
	UnmanagedPointer->applyGravity();
}

void DiscreteDynamicsWorld::DebugDrawConstraint(TypedConstraint^ constraint)
{
	UnmanagedPointer->debugDrawConstraint(constraint->UnmanagedPointer);
}

CollisionWorld^ DiscreteDynamicsWorld::CollisionWorld::get()
{
	return gcnew BulletSharp::CollisionWorld(this->UnmanagedPointer->getCollisionWorld());
}

SimulationIslandManager^ DiscreteDynamicsWorld::SimulationIslandManager::get()
{
	return gcnew BulletSharp::SimulationIslandManager(UnmanagedPointer->getSimulationIslandManager());
}

void DiscreteDynamicsWorld::SetNumTasks (int numTasks)
{
	UnmanagedPointer->setNumTasks(numTasks);
}

bool DiscreteDynamicsWorld::SynchronizeAllMotionStates::get()
{
	return UnmanagedPointer->getSynchronizeAllMotionStates();
}
void DiscreteDynamicsWorld::SynchronizeAllMotionStates::set(bool value)
{
	return UnmanagedPointer->setSynchronizeAllMotionStates(value);
}

void DiscreteDynamicsWorld::SynchronizeSingleMotionState(RigidBody^ body)
{
	UnmanagedPointer->synchronizeSingleMotionState(body->UnmanagedPointer);
}

btDiscreteDynamicsWorld* DiscreteDynamicsWorld::UnmanagedPointer::get()
{
	return (btDiscreteDynamicsWorld*)DynamicsWorld::UnmanagedPointer;
}
