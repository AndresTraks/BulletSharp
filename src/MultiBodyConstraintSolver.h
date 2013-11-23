#pragma once

#ifndef DISABLE_FEATHERSTONE

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	public ref class MultiBodyConstraintSolver : SequentialImpulseConstraintSolver
	{
	internal:
		MultiBodyConstraintSolver(btMultiBodyConstraintSolver* native);

	public:
		MultiBodyConstraintSolver();

		//void SolveMultiBodyGroup(CollisionObject^ bodies, int numBodies, PersistentManifold^ manifold, int numManifolds, TypedConstraint^ constraints, int numConstraints, MultiBodyConstraint^ multiBodyConstraints, int numMultiBodyConstraints, ContactSolverInfo^ info, IDebugDraw^ debugDrawer, Dispatcher^ dispatcher);
	};
};

#endif
