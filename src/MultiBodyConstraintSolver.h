#pragma once

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class ContactSolverInfo;
	ref class Dispatcher;
	ref class MultiBodyConstraint;
	ref class PersistentManifold;
	ref class TypedConstraint;
	interface class IDebugDraw;

	public ref class MultiBodyConstraintSolver : SequentialImpulseConstraintSolver
	{
	internal:
		MultiBodyConstraintSolver(btMultiBodyConstraintSolver* native);

	public:
		MultiBodyConstraintSolver();
/*
		void SolveMultiBodyGroup(CollisionObject^ bodies, int numBodies, PersistentManifold^ manifold,
			int numManifolds, TypedConstraint^ constraints, int numConstraints, MultiBodyConstraint^ multiBodyConstraints,
			int numMultiBodyConstraints, ContactSolverInfo^ info, IDebugDraw^ debugDrawer,
			Dispatcher^ dispatcher);
*/
	};
};
