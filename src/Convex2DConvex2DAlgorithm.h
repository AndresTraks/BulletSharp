#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	ref class ConvexPenetrationDepthSolver;
	value struct PersistentManifold;

	public ref class Convex2DConvex2DAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
			ConvexPenetrationDepthSolver^ _pdSolver;
			SimplexSolverInterface^ _simplexSolver;

		public:
			CreateFunc(SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ pdSolver);

			property int MinimumPointsPerturbationThreshold
			{
				int get();
				void set(int value);
			}

			property int NumPerturbationIterations
			{
				int get();
				void set(int value);
			}

			property ConvexPenetrationDepthSolver^ PdSolver
			{
				ConvexPenetrationDepthSolver^ get();
				void set(ConvexPenetrationDepthSolver^ value);
			}

			property VoronoiSimplexSolver^ SimplexSolver
			{
				VoronoiSimplexSolver^ get();
				void set(VoronoiSimplexSolver^ value);
			}
		};

		Convex2DConvex2DAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ pdSolver,
			int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		void SetLowLevelOfDetail(bool useLowLevel);

		property PersistentManifold Manifold
		{
			PersistentManifold get();
		}
	};
};
