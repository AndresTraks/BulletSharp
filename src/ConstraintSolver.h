#pragma once

// Fully implemented as of 11 May 2010

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class ContactSolverInfo;
	ref class Dispatcher;
	ref class PersistentManifold;
	ref class StackAlloc;
	ref class TypedConstraint;
	interface class IDebugDraw;

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
		void AllSolved(ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
			IDebugDraw^ debugDrawer,
#endif
			StackAlloc^ stackAlloc);
		void PrepareSolve(int numBodies, int numManifolds);
		void Reset();
		btScalar SolveGroup(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifold,
			array<TypedConstraint^>^ constraints, ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
			IDebugDraw^ debugDrawer,
#endif
			StackAlloc^ stackAlloc, Dispatcher^ dispatcher);

	internal:
		property btConstraintSolver* UnmanagedPointer
		{
			virtual btConstraintSolver* get();
			void set(btConstraintSolver* value);
		}
#endif
	};
};
