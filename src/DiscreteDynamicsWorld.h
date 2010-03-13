#pragma once

#include "DynamicsWorld.h"

namespace BulletSharp
{
	ref class ConstraintSolver;
	ref class Dispatcher;

	public ref class DiscreteDynamicsWorld : DynamicsWorld
	{
	internal:
		DiscreteDynamicsWorld(btDiscreteDynamicsWorld* world);
	public:
#ifndef DISABLE_CONSTRAINTS
		DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
			BroadphaseInterface^ pairCache, ConstraintSolver^ constraintSolver,
			CollisionConfiguration^ collisionConfiguration);
#else
		DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
			BroadphaseInterface^ pairCache,
			CollisionConfiguration^ collisionConfiguration);
#endif

		void SetGravity(btScalar x, btScalar y, btScalar z);

	internal:
		property btDiscreteDynamicsWorld* UnmanagedPointer
		{
			btDiscreteDynamicsWorld* get() new;
		}
	};
};
