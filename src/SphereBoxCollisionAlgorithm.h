#pragma once

// Fully implemented as of 09 May 2010

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class SphereBoxCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		SphereBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1, bool isSwapped);

		btScalar GetSphereDistance(CollisionObject^ boxObj, Vector3 v3PointOnBox,
			Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius);
		btScalar GetSpherePenetration(CollisionObject^ boxObj, Vector3 v3PointOnBox, Vector3 v3PointOnSphere,
			Vector3 v3SphereCenter, btScalar fRadius, Vector3 aabbMin, Vector3 aabbMax);

	internal:
		property btSphereBoxCollisionAlgorithm* UnmanagedPointer
		{
			btSphereBoxCollisionAlgorithm* get() new;
		}
	};
};
