#pragma once

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

	private:
		Object^ _userObject;
	internal:
		InternalTickCallback^ _callback;

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
};
