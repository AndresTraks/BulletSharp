#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"
#include "SphereBoxCollisionAlgorithm.h"

SphereBoxCollisionAlgorithm::CreateFunc::CreateFunc(btSphereBoxCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

SphereBoxCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btSphereBoxCollisionAlgorithm::CreateFunc(), false)
{
}


#define Native static_cast<btSphereBoxCollisionAlgorithm*>(_native)

SphereBoxCollisionAlgorithm::SphereBoxCollisionAlgorithm(PersistentManifold mf,
	CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	bool isSwapped)
	: ActivatingCollisionAlgorithm(new btSphereBoxCollisionAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

bool SphereBoxCollisionAlgorithm::GetSphereDistance(CollisionObjectWrapper^ boxObjWrap,
	Vector3% v3PointOnBox, Vector3% normal, btScalar% penetrationDepth, Vector3 v3SphereCenter,
	btScalar fRadius, btScalar maxContactDistance)
{
	btVector3* v3PointOnBoxTemp = ALIGNED_NEW(btVector3);
	btVector3* normalTemp = ALIGNED_NEW(btVector3);
	VECTOR3_CONV(v3SphereCenter);
	btScalar penetrationDepthTemp;
	bool ret = Native->getSphereDistance(boxObjWrap->_native, *v3PointOnBoxTemp,
		*normalTemp, penetrationDepthTemp, VECTOR3_USE(v3SphereCenter),
		fRadius, maxContactDistance);
	Math::BtVector3ToVector3(v3PointOnBoxTemp, v3PointOnBox);
	Math::BtVector3ToVector3(normalTemp, normal);
	penetrationDepth = penetrationDepthTemp;
	ALIGNED_FREE(v3PointOnBoxTemp);
	ALIGNED_FREE(normalTemp);
	VECTOR3_DEL(v3SphereCenter);
	return ret;
}

btScalar SphereBoxCollisionAlgorithm::GetSpherePenetration(Vector3 boxHalfExtent,
	Vector3 sphereRelPos, [Out] Vector3% closestPoint, [Out] Vector3% normal)
{
	VECTOR3_CONV(boxHalfExtent);
	VECTOR3_CONV(sphereRelPos);
	btVector3* closestPointTemp = ALIGNED_NEW(btVector3);
	btVector3* normalTemp = ALIGNED_NEW(btVector3);
	btScalar ret = Native->getSpherePenetration(VECTOR3_USE(boxHalfExtent), VECTOR3_USE(sphereRelPos),
		*closestPointTemp, *normalTemp);
	Math::BtVector3ToVector3(closestPointTemp, closestPoint);
	Math::BtVector3ToVector3(normalTemp, normal);
	VECTOR3_DEL(boxHalfExtent);
	VECTOR3_DEL(sphereRelPos);
	ALIGNED_FREE(closestPointTemp);
	ALIGNED_FREE(normalTemp);
	return ret;
}

#endif
