#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
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
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
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
