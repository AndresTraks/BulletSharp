#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
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

			property int PerturbationIterationsCount
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
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped, int numPerturbationIterations,
			int minimumPointsPerturbationThreshold);

		void CollideSingleContact(Quaternion perturbeRot, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);

	internal:
		property btConvexPlaneCollisionAlgorithm* UnmanagedPointer
		{
			btConvexPlaneCollisionAlgorithm* get() new;
		}
	};
};
