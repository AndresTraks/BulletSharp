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

	public:
		MultiBodyDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, MultiBodyConstraintSolver^ constraintSolver, CollisionConfiguration^ collisionConfiguration);

		void AddMultiBody(MultiBody^ body, short group, short mask);
		void AddMultiBody(MultiBody^ body, short group);
		void AddMultiBody(MultiBody^ body);
		void AddMultiBodyConstraint(MultiBodyConstraint^ constraint);
		void RemoveMultiBody(MultiBody^ body);
		void RemoveMultiBodyConstraint(MultiBodyConstraint^ constraint);
	};
};
