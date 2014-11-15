#pragma once

#include "DynamicsWorld.h"

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
		DiscreteDynamicsWorld(btDiscreteDynamicsWorld* native);

#ifndef DISABLE_UNCOMMON
	private:
		SimulationIslandManager^ _simulationIslandManager;
#endif

	public:
		DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
			BulletSharp::ConstraintSolver^ constraintSolver,
#endif
			CollisionConfiguration^ collisionConfiguration);

		void ApplyGravity();
#if !defined(DISABLE_CONSTRAINTS) && !defined (DISABLE_DEBUGDRAW)
		void DebugDrawConstraint(TypedConstraint^ constraint);
#endif
		void SetNumTasks(int numTasks);
		void SynchronizeSingleMotionState(RigidBody^ body);

		property bool ApplySpeculativeContactRestitution
		{
			bool get();
			void set(bool enable);
		}

		property bool LatencyMotionStateInterpolation
		{
			bool get();
			void set(bool latencyInterpolation);
		}
#ifndef DISABLE_UNCOMMON
		property SimulationIslandManager^ SimulationIslandManager
		{
			BulletSharp::SimulationIslandManager^ get();
		}
#endif

		property bool SynchronizeAllMotionStates
		{
			bool get();
			void set(bool synchronizeAll);
		}
	};
};
