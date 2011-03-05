#pragma once

// Fully implemented as of 18 Nov 2010

#include "CollisionWorld.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class ActionInterface;
	ref class ConstraintSolver;
	ref class ContactSolverInfo;
	ref class RigidBody;
	ref class TypedConstraint;

	public ref class DynamicsWorld : CollisionWorld
	{
	public:
		delegate void InternalTickCallback(DynamicsWorld^ world, btScalar timeStep);

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

	internal:
		DynamicsWorld(btDynamicsWorld* world);

	public:
		void AddAction(ActionInterface^ actionInterface);

#ifndef DISABLE_CONSTRAINTS
		void AddConstraint(TypedConstraint^ constraint,	bool disableCollisionsBetweenLinkedBodies);
		void AddConstraint(TypedConstraint^ constraint);
		void RemoveConstraint(TypedConstraint^ constraint);
		TypedConstraint^ GetConstraint(int index);
#endif
		void AddRigidBody(RigidBody^ rigidBody, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask);
		void AddRigidBody(RigidBody^ rigidBody);
		void ClearForces();
		void RemoveAction(ActionInterface^ actionInterface);
		void RemoveRigidBody(RigidBody^ rigidBody);
		void SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo, bool isPreTick);
		void SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo);
		void SetInternalTickCallback(InternalTickCallback^ cb);
		int StepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep);
		int StepSimulation(btScalar timeStep, int maxSubSteps);
		int StepSimulation(btScalar timeStep);
		void SynchronizeMotionStates();

#ifndef DISABLE_CONSTRAINTS
		property ConstraintSolver^ ConstraintSolver
		{
			BulletSharp::ConstraintSolver^ get();
			void set(BulletSharp::ConstraintSolver^ value);
		}

		property ContactSolverInfo^ SolverInfo
		{
			ContactSolverInfo^ get();
		}

		property int NumConstraints
		{
			int get();
		}
#endif

		virtual property Vector3 Gravity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property DynamicsWorldType WorldType
		{
			DynamicsWorldType get();
		}

		property Object^ WorldUserInfo
		{
			Object^ get();
			void set(Object^ value);
		}

	internal:
		property btDynamicsWorld* UnmanagedPointer
		{
			btDynamicsWorld* get() new;
		}
	};

	// Use the user info value to also store our own stuff.
	ref class UserInfoWrapper
	{
	private:
		Object^ _userObject;
		DynamicsWorld::InternalTickCallback^ _callback;

	public:
		UserInfoWrapper(Object^ userObject);
		UserInfoWrapper();

		property DynamicsWorld::InternalTickCallback^ Callback
		{
			DynamicsWorld::InternalTickCallback^ get();
			void set(DynamicsWorld::InternalTickCallback^ value);
		}

		property Object^ UserObject
		{
			Object^ get();
			void set(Object^ value);
		}
	};
};
