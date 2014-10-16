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
	internal:
		MultiBodyDynamicsWorld(btMultiBodyDynamicsWorld* native);

	private:
		System::Collections::Generic::List<MultiBody^>^ _bodies;
#ifndef DISABLE_CONSTRAINTS
		System::Collections::Generic::List<MultiBodyConstraint^>^ _constraints;
#endif

	public:
		MultiBodyDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
			MultiBodyConstraintSolver^ constraintSolver, CollisionConfiguration^ collisionConfiguration);

		void AddMultiBody(MultiBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask);
		void AddMultiBody(MultiBody^ body, short group, short mask);
		void AddMultiBody(MultiBody^ body);
#ifndef DISABLE_CONSTRAINTS
		void AddMultiBodyConstraint(MultiBodyConstraint^ constraint);
#endif
		void RemoveMultiBody(MultiBody^ body);
#ifndef DISABLE_CONSTRAINTS
		void RemoveMultiBodyConstraint(MultiBodyConstraint^ constraint);
#endif
	};
};
