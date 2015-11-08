#pragma once

#include "DiscreteDynamicsWorld.h"

namespace BulletSharp
{
	ref class Dispatcher;
	ref class MultiBody;
	ref class MultiBodyConstraint;
	ref class MultiBodyConstraintSolver;

	public ref class MultiBodyDynamicsWorld : DiscreteDynamicsWorld
	{
	private:
		List<MultiBody^>^ _bodies;
#ifndef DISABLE_CONSTRAINTS
		List<MultiBodyConstraint^>^ _constraints;
#endif

	public:
		MultiBodyDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
			MultiBodyConstraintSolver^ constraintSolver, CollisionConfiguration^ collisionConfiguration);

		void AddMultiBody(MultiBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask);
		void AddMultiBody(MultiBody^ body, short group, short mask);
		void AddMultiBody(MultiBody^ body);
#ifndef DISABLE_CONSTRAINTS
		void AddMultiBodyConstraint(MultiBodyConstraint^ constraint);
#ifndef DISABLE_DEBUGDRAW
		void DebugDrawMultiBodyConstraint(MultiBodyConstraint^ constraint);
#endif
#endif
		void ClearMultiBodyConstraintForces();
		void ClearMultiBodyForces();
		void ForwardKinematics();
		MultiBody^ GetMultiBody(int mbIndex);
		MultiBodyConstraint^ GetMultiBodyConstraint(int constraintIndex);
		void IntegrateTransforms(btScalar timeStep);
		void RemoveMultiBody(MultiBody^ body);
#ifndef DISABLE_CONSTRAINTS
		void RemoveMultiBodyConstraint(MultiBodyConstraint^ constraint);
#endif
		property int NumMultibodies
		{
			int get();
		}

		property int NumMultiBodyConstraints
		{
			int get();
		}
	};
};
