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

#define Native static_cast<btDiscreteDynamicsWorld*>(_native)

DiscreteDynamicsWorld::DiscreteDynamicsWorld(btDiscreteDynamicsWorld* native)
	: DynamicsWorld(native)
{
}

DiscreteDynamicsWorld::DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration)
	: DynamicsWorld(new btDiscreteDynamicsWorld(dispatcher->_native, pairCache->_native,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		0,
#endif
		collisionConfiguration->_native))
{
#ifndef DISABLE_CONSTRAINTS
	_constraintSolver = constraintSolver;
#endif
	Dispatcher = dispatcher;
	_broadphase = pairCache;
}

void DiscreteDynamicsWorld::ApplyGravity()
{
	Native->applyGravity();
}

#if !defined(DISABLE_CONSTRAINTS) && !defined (DISABLE_DEBUGDRAW)
void DiscreteDynamicsWorld::DebugDrawConstraint(TypedConstraint^ constraint)
{
	Native->debugDrawConstraint(constraint->_native);
}
#endif

void DiscreteDynamicsWorld::SetNumTasks(int numTasks)
{
	Native->setNumTasks(numTasks);
}

void DiscreteDynamicsWorld::SynchronizeSingleMotionState(RigidBody^ body)
{
	Native->synchronizeSingleMotionState((btRigidBody*)body->_native);
}

bool DiscreteDynamicsWorld::ApplySpeculativeContactRestitution::get()
{
	return Native->getApplySpeculativeContactRestitution();
}
void DiscreteDynamicsWorld::ApplySpeculativeContactRestitution::set(bool enable)
{
	Native->setApplySpeculativeContactRestitution(enable);
}

bool DiscreteDynamicsWorld::LatencyMotionStateInterpolation::get()
{
	return Native->getLatencyMotionStateInterpolation();
}
void DiscreteDynamicsWorld::LatencyMotionStateInterpolation::set(bool latencyInterpolation)
{
	Native->setLatencyMotionStateInterpolation(latencyInterpolation);
}

#ifndef DISABLE_UNCOMMON
SimulationIslandManager^ DiscreteDynamicsWorld::SimulationIslandManager::get()
{
	if (_simulationIslandManager == nullptr)
	{
		_simulationIslandManager = gcnew BulletSharp::SimulationIslandManager(Native->getSimulationIslandManager(), true);
	}
	return _simulationIslandManager;
}
#endif

bool DiscreteDynamicsWorld::SynchronizeAllMotionStates::get()
{
	return Native->getSynchronizeAllMotionStates();
}
void DiscreteDynamicsWorld::SynchronizeAllMotionStates::set(bool synchronizeAll)
{
	Native->setSynchronizeAllMotionStates(synchronizeAll);
}
