#pragma once

// Fully implemented as of 24 apr 2010

#include "DynamicsWorld.h"
#include "Enums.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class ConstraintSolver;
	ref class Dispatcher;
	ref class RigidBody;
	ref class SimulationIslandManager;
	ref class TypedConstraint;

	public ref class DiscreteDynamicsWorld : DynamicsWorld
	{
	internal:
		DiscreteDynamicsWorld(btDiscreteDynamicsWorld* world);

	public:
		DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
			BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
			BulletSharp::ConstraintSolver^ constraintSolver,
#endif
			CollisionConfiguration^ collisionConfiguration);

		void AddRigidBody(RigidBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask);
		void ApplyGravity();
#if !defined(DISABLE_CONSTRAINTS) && !defined (DISABLE_DEBUGDRAW)
		void DebugDrawConstraint(TypedConstraint^ constraint);
#endif
		void SetNumTasks (int numTasks);
		void SynchronizeSingleMotionState(RigidBody^ body);

		property CollisionWorld^ CollisionWorld
		{
			BulletSharp::CollisionWorld^ get();
		}

		property SimulationIslandManager^ SimulationIslandManager
		{
			BulletSharp::SimulationIslandManager^ get();
		}

		property bool SynchronizeAllMotionStates
		{
			bool get();
			void set(bool value);
		}

	internal:
		property btDiscreteDynamicsWorld* UnmanagedPointer
		{
			btDiscreteDynamicsWorld* get() new;
		}
	};
};
