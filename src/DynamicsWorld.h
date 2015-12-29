#pragma once

#include "CollisionWorld.h"

namespace BulletSharp
{
	ref class ConstraintSolver;
	ref class ContactSolverInfo;
	ref class RigidBody;
	ref class TypedConstraint;
	interface class IAction;
	class ActionInterfaceWrapper;

	public ref class DynamicsWorld abstract : CollisionWorld
	{
	public:
		delegate void InternalTickCallback(DynamicsWorld^ world, btScalar timeStep);

	private:
		[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
		delegate void InternalTickCallbackUnmanagedDelegate(IntPtr world, btScalar timeStep);

	private:
		Object^ _userObject;
		InternalTickCallback^ _callback;
		InternalTickCallbackUnmanagedDelegate^ _callbackUnmanaged;
		ContactSolverInfo^ _solverInfo;
		Dictionary<IAction^, IntPtr>^ _actions;
		List<TypedConstraint^>^ _constraints;

	protected:
		ConstraintSolver^ _constraintSolver;

	internal:
		DynamicsWorld(btDynamicsWorld* native);

		!DynamicsWorld();
		~DynamicsWorld();

	public:
		void AddAction(IAction^ action);
#ifndef DISABLE_CONSTRAINTS
		void AddConstraint(TypedConstraint^ constraint, bool disableCollisionsBetweenLinkedBodies);
		void AddConstraint(TypedConstraint^ constraint);
#endif
		void AddRigidBody(RigidBody^ body);
		void AddRigidBody(RigidBody^ body, CollisionFilterGroups group, CollisionFilterGroups mask);
		void AddRigidBody(RigidBody^ body, short group, short mask);
		void ClearForces();
#ifndef DISABLE_CONSTRAINTS
		TypedConstraint^ GetConstraint(int index);
#endif
		void InternalTickCallbackUnmanaged(IntPtr world, btScalar timeStep);
		void RemoveAction(IAction^ action);
#ifndef DISABLE_CONSTRAINTS
		void RemoveConstraint(TypedConstraint^ constraint);
#endif
		void RemoveRigidBody(RigidBody^ body);
		void SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo,
			bool isPreTick);
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
			void set(BulletSharp::ConstraintSolver^ solver);
		}
#endif

		property Vector3 Gravity
		{
			Vector3 get();
			void set(Vector3 gravity);
		}

#ifndef DISABLE_CONSTRAINTS
		property int NumConstraints
		{
			int get();
		}
#endif

		property ContactSolverInfo^ SolverInfo
		{
			ContactSolverInfo^ get();
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
	};
};
