#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	value struct PersistentManifold;

	public ref class ConvexPlaneCollisionAlgorithm : CollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btConvexPlaneCollisionAlgorithm::CreateFunc* native);

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
		};

	internal:
		ConvexPlaneCollisionAlgorithm(btConvexPlaneCollisionAlgorithm* native);

	public:
		ConvexPlaneCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped,
			int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		void CollideSingleContact(Quaternion perturbeRot, CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap, DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);
	};
};
