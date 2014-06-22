#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	ref class ConvexPenetrationDepthSolver;
	ref class PersistentManifold;

	public ref class Convex2DConvex2DAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		private:
			SimplexSolverInterface^ _simplexSolver;
			ConvexPenetrationDepthSolver^ _pdSolver;

		public:
			CreateFunc(SimplexSolverInterface^ simplexSolver,
				ConvexPenetrationDepthSolver^ pdSolver);
		};

		Convex2DConvex2DAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		property PersistentManifold^ Manifold
		{
			PersistentManifold^ get();
		}
	};
};
