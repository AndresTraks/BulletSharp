#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;

	public ref class SphereSphereCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		SphereSphereCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap);
		SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);

	internal:
		property btSphereSphereCollisionAlgorithm* UnmanagedPointer
		{
			btSphereSphereCollisionAlgorithm* get() new;
		}
	};
};
