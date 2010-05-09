#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class PersistentManifold;

	public ref class ConvexPlaneCollisionAlgorithm : CollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();

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

		internal:
			property btConvexPlaneCollisionAlgorithm::CreateFunc* UnmanagedPointer
			{
				btConvexPlaneCollisionAlgorithm::CreateFunc* get() new;
			}
		};

		ConvexPlaneCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ col0, CollisionObject^ col1, bool isSwapped, int numPerturbationIterations,
			int minimumPointsPerturbationThreshold);

		void CollideSingleContact(Quaternion perturbeRot, CollisionObject^ body0, CollisionObject^ body1,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);

	internal:
		property btConvexPlaneCollisionAlgorithm* UnmanagedPointer
		{
			btConvexPlaneCollisionAlgorithm* get() new;
		}
	};
};
