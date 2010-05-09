#pragma once

// Fully implemented as of 10 May 2010

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class SphereTriangleCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		SphereTriangleCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, bool isSwapped);
		SphereTriangleCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);

	internal:
		property btSphereTriangleCollisionAlgorithm* UnmanagedPointer
		{
			btSphereTriangleCollisionAlgorithm* get() new;
		}
	};
};
