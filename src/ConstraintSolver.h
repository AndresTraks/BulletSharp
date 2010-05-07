#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class ConstraintSolver : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btConstraintSolver* _solver;

	internal:
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
#ifndef DISABLE_CONSTRAINTS
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
#endif
	};
};
