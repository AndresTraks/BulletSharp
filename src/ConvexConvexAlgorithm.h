#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	ref class ConvexPenetrationDepthSolver;

	public ref class ConvexConvexAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
			ConvexPenetrationDepthSolver^ _pdSolver;

		internal:
			CreateFunc(btConvexConvexAlgorithm::CreateFunc* native);

		public:
			CreateFunc(ConvexPenetrationDepthSolver^ pdSolver);

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
		};

		ConvexConvexAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations,
			int minimumPointsPerturbationThreshold);

		void SetLowLevelOfDetail(bool useLowLevel);

		property PersistentManifold Manifold
		{
			PersistentManifold get();
		}
	};
};
