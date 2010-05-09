#pragma once

// Fully implemented as of 10 May 2010

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class SphereSphereCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		SphereSphereCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1);
		SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);

	internal:
		property btSphereSphereCollisionAlgorithm* UnmanagedPointer
		{
			btSphereSphereCollisionAlgorithm* get() new;
		}
	};
};
