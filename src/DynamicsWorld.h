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
			void AddRigidBody(RigidBody^ rigidBody);
			void AddAction(ActionInterface^ actionInterface);
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
