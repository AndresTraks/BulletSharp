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
		DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
			BroadphaseInterface^ pairCache, ConstraintSolver^ constraintSolver,
			CollisionConfiguration^ collisionConfiguration);

		void SetGravity(btScalar x, btScalar y, btScalar z);

	internal:
		property btDiscreteDynamicsWorld* UnmanagedPointer
		{
			btDiscreteDynamicsWorld* get() new;
		}
	};
};
