#pragma once

#include "CollisionWorld.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class ActionInterface;
	ref struct ContactSolverInfo;
	ref class RigidBody;
	ref class TypedConstraint;

	public ref class DynamicsWorld abstract : CollisionWorld
	{
	public:
		ref class RayResultCallback abstract : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btDynamicsWorld::RayResultCallback* _callback;

		protected:
			RayResultCallback(btDynamicsWorld::RayResultCallback* callback);
		public:
			!RayResultCallback();
		protected:
			~RayResultCallback();
		public:
			property bool IsDisposed
			{
				virtual bool get();
			}

		internal:
			property btDynamicsWorld::RayResultCallback* UnmanagedPointer
			{
				virtual btDynamicsWorld::RayResultCallback* get();
				void set(btDynamicsWorld::RayResultCallback* value);
			}
		};

		ref class ClosestRayResultCallback : RayResultCallback
		{
		public:
			ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld);
		};

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

		property ContactSolverInfo^ SolverInfo
		{
			ContactSolverInfo^ get();
		}

	internal:
		property btDynamicsWorld* UnmanagedPointer
		{
			btDynamicsWorld* get() new;
		}
	};
};
