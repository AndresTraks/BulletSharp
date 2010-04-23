#pragma once

// Fully implemented as of 02 Apr 2010

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class PersistentManifold;

	public ref class Convex2dConvex2dAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc(SimplexSolverInterface^ simplexSolver,
				ConvexPenetrationDepthSolver^ pdSolver);
		};

		Convex2dConvex2dAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		property PersistentManifold^ Manifold
		{
			PersistentManifold^ get();
		}

	internal:
		property btConvex2dConvex2dAlgorithm* UnmanagedPointer
		{
			virtual btConvex2dConvex2dAlgorithm* get() new;
		}
	};
};
