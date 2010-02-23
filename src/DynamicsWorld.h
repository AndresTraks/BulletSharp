#pragma once

#include "ActionInterface.h"
#include "CollisionWorld.h"
#include "RigidBody.h"

namespace BulletSharp
{
	public ref class DynamicsWorld abstract : BulletSharp::CollisionWorld
	{
	protected:
		DynamicsWorld(btDynamicsWorld* world) : CollisionWorld(world) {}

	public:
		void AddAction(ActionInterface^ actionInterface);
		void AddConstraint(TypedConstraint^ constraint,
			bool disableCollisionsBetweenLinkedBodies);
		void AddConstraint(TypedConstraint^ constraint);
		void RemoveConstraint(TypedConstraint^ constraint);
		void AddRigidBody(RigidBody^ rigidBody);
		void StepSimulation(btScalar timeStep);
		void DebugDrawWorld();

		virtual property Vector3 Gravity
		{
			Vector3 get();
			void set(Vector3 value);
		}

	internal:
		property btDynamicsWorld* UnmanagedPointer
		{
			btDynamicsWorld* get() new;
		}
	};
};
