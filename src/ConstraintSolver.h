#pragma once

namespace BulletSharp
{
	ref class CollisionObject;
	ref class ContactSolverInfo;
	ref class Dispatcher;
	ref class PersistentManifold;
	ref class TypedConstraint;
	interface class IDebugDraw;

	public ref class ConstraintSolver abstract : ITrackingDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btConstraintSolver* _native;
		ConstraintSolver(btConstraintSolver* native);
		static ConstraintSolver^ GetManaged(btConstraintSolver* native);

	private:
		bool _preventDelete;

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
		void AllSolved(ContactSolverInfo^ info
#ifndef DISABLE_DEBUGDRAW
			, IDebugDraw^ debugDrawer
#endif
			);
		void PrepareSolve(int numBodies, int numManifolds);
		void Reset();
		btScalar SolveGroup(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifold,
			array<TypedConstraint^>^ constraints, ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
			IDebugDraw^ debugDrawer,
#endif
			Dispatcher^ dispatcher);
#endif
#ifndef DISABLE_CONSTRAINTS
		property ConstraintSolverType SolverType
		{
			ConstraintSolverType get();
		}
#endif
	};
};
