#pragma once

#include "ConstraintSolver.h"
#include "Dispatcher.h"
#include "DynamicsWorld.h"

namespace BulletSharp
{
	public ref class DiscreteDynamicsWorld : BulletSharp::DynamicsWorld
	{
		public:
			DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, ConstraintSolver^ constraintSolver, CollisionConfiguration^ collisionConfiguration);

			void SetGravity(btScalar x, btScalar y, btScalar z);

		internal:
			property btDiscreteDynamicsWorld* UnmanagedPointer
			{
				btDiscreteDynamicsWorld* get() new;
			}
	};
};
