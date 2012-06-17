#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;

	public ref class SphereBoxCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		SphereBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped);

		btScalar GetSphereDistance(CollisionObjectWrapper^ boxObjWrap, Vector3 v3PointOnBox,
			Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius);
		btScalar GetSpherePenetration(CollisionObjectWrapper^ boxObjWrap, Vector3 v3PointOnBox, Vector3 v3PointOnSphere,
			Vector3 v3SphereCenter, btScalar fRadius, Vector3 aabbMin, Vector3 aabbMax);

	internal:
		property btSphereBoxCollisionAlgorithm* UnmanagedPointer
		{
			btSphereBoxCollisionAlgorithm* get() new;
		}
	};
};
