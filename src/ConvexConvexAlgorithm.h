#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;

	public ref class ConvexConvexAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
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

			property SimplexSolverInterface^ SimplexSolver
			{
				SimplexSolverInterface^ get();
				void set(SimplexSolverInterface^ value);
			}

		internal:
			property btConvexConvexAlgorithm::CreateFunc* UnmanagedPointer
			{
				btConvexConvexAlgorithm::CreateFunc* get() new;
			}
		};

		ConvexConvexAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		void SetLowLevelOfDetail(bool useLowLevel);

		property PersistentManifold^ Manifold
		{
			PersistentManifold^ get();
		}

	internal:
		property btConvexConvexAlgorithm* UnmanagedPointer
		{
			btConvexConvexAlgorithm* get() new;
		}
	};
};
