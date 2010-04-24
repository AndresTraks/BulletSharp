#pragma once

#include "DynamicsWorld.h"
#include "Enums.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class ConstraintSolver;
	ref class Dispatcher;
	ref class RigidBody;
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
		void DebugDrawConstraint(TypedConstraint^ constraint);

		void SetGravity(btScalar x, btScalar y, btScalar z);

		property CollisionWorld^ CollisionWorld
		{
			BulletSharp::CollisionWorld^ get();
		}

	internal:
		property btDiscreteDynamicsWorld* UnmanagedPointer
		{
			btDiscreteDynamicsWorld* get() new;
		}
	};
};
