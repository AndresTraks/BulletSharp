#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"
#include "SphereBoxCollisionAlgorithm.h"

SphereBoxCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSphereBoxCollisionAlgorithm::CreateFunc())
{
}

SphereBoxCollisionAlgorithm::SphereBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: ActivatingCollisionAlgorithm(new btSphereBoxCollisionAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer,
	body0Wrap->_unmanaged, body1Wrap->_unmanaged, isSwapped))
{
}

bool SphereBoxCollisionAlgorithm::GetSphereDistance(CollisionObjectWrapper^ boxObjWrap, Vector3 v3PointOnBox,
	Vector3 normal, btScalar% penetrationDepth, Vector3 v3SphereCenter, btScalar fRadius, btScalar maxContactDistance)
{
	VECTOR3_DEF(v3PointOnBox);
	VECTOR3_DEF(normal);
	VECTOR3_DEF(v3SphereCenter);
	btScalar penetrationDepthTemp = penetrationDepth;

	bool ret = UnmanagedPointer->getSphereDistance(boxObjWrap->_unmanaged, VECTOR3_USE(v3PointOnBox),
		VECTOR3_USE(normal), penetrationDepthTemp, VECTOR3_USE(v3SphereCenter), fRadius, maxContactDistance);

	VECTOR3_DEL(v3PointOnBox);
	VECTOR3_DEL(normal);
	VECTOR3_DEL(v3SphereCenter);

	penetrationDepth = penetrationDepthTemp;
	return ret;
}

btScalar SphereBoxCollisionAlgorithm::GetSpherePenetration(Vector3 boxHalfExtent, Vector3 sphereRelPos,
	Vector3 closestPoint, Vector3 normal)
{
	VECTOR3_DEF(boxHalfExtent);
	VECTOR3_DEF(sphereRelPos);
	VECTOR3_DEF(closestPoint);
	VECTOR3_DEF(normal);

	btScalar ret = UnmanagedPointer->getSpherePenetration(VECTOR3_USE(boxHalfExtent), VECTOR3_USE(sphereRelPos),
		VECTOR3_USE(closestPoint), VECTOR3_USE(normal));

	VECTOR3_DEL(boxHalfExtent);
	VECTOR3_DEL(sphereRelPos);
	VECTOR3_DEL(closestPoint);
	VECTOR3_DEL(normal);

	return ret;
}

btSphereBoxCollisionAlgorithm* SphereBoxCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereBoxCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
