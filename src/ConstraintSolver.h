#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class ConstraintSolver abstract : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btConstraintSolver* _solver;

	protected:
		ConstraintSolver(btConstraintSolver* solver);
	public:
		!ConstraintSolver();
	protected:
		~ConstraintSolver();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

		//void AllSolved(ContactSolverInfo^, DebugDraw^, StackAlloc^);
		//virtual void PrepareSolve(int, int);
		void Reset();
		//btScalar SolveGroup(CollisionObject^ bodies,
		//	int	numBodies,
		//	PersistentManifold^	manifold,
		//	int	numManifolds,
		//	TypedConstraint^ constraints,
		//	int	numConstraints,
		//	ContactSolverInfo^ info,
		//	DebugDraw^ debugDrawer,
		//	StackAlloc^ stackAlloc,
		//	IDispatcher^ dispatcher
		//);

	public:
		property btConstraintSolver* UnmanagedPointer
		{
			virtual btConstraintSolver* get();
			void set(btConstraintSolver* value);
		}
	};
};
