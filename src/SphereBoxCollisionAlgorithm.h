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
		internal:
			CreateFunc(btSphereBoxCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		SphereBoxCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			bool isSwapped);

		bool GetSphereDistance(CollisionObjectWrapper^ boxObjWrap, [Out] Vector3% v3PointOnBox,
			[Out] Vector3% normal, [Out] btScalar% penetrationDepth, Vector3 v3SphereCenter, btScalar fRadius,
			btScalar maxContactDistance);
		btScalar GetSpherePenetration(Vector3 boxHalfExtent, Vector3 sphereRelPos,
			[Out] Vector3% closestPoint, [Out] Vector3% normal);
	};
};
