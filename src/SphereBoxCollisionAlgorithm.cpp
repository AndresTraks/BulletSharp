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

btScalar SphereBoxCollisionAlgorithm::GetSphereDistance(CollisionObjectWrapper^ boxObjWrap, Vector3 v3PointOnBox,
	Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius)
{
	VECTOR3_DEF(v3PointOnBox);
	VECTOR3_DEF(v3PointOnSphere);
	VECTOR3_DEF(v3SphereCenter);

	btScalar ret = UnmanagedPointer->getSphereDistance(boxObjWrap->_unmanaged, VECTOR3_USE(v3PointOnBox),
		VECTOR3_USE(v3PointOnSphere), VECTOR3_USE(v3SphereCenter), fRadius);

	VECTOR3_DEL(v3PointOnBox);
	VECTOR3_DEL(v3PointOnSphere);
	VECTOR3_DEL(v3SphereCenter);

	return ret;
}

btScalar SphereBoxCollisionAlgorithm::GetSpherePenetration(CollisionObjectWrapper^ boxObjWrap, Vector3 v3PointOnBox,
	Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(v3PointOnBox);
	VECTOR3_DEF(v3PointOnSphere);
	VECTOR3_DEF(v3SphereCenter);
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	btScalar ret = UnmanagedPointer->getSpherePenetration(boxObjWrap->_unmanaged,
		VECTOR3_USE(v3PointOnBox), VECTOR3_USE(v3PointOnSphere),
		VECTOR3_USE(v3SphereCenter), fRadius, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(v3PointOnBox);
	VECTOR3_DEL(v3PointOnSphere);
	VECTOR3_DEL(v3SphereCenter);
	VECTOR3_DEL(aabbMinTemp);
	VECTOR3_DEL(aabbMaxTemp);

	return ret;
}

btSphereBoxCollisionAlgorithm* SphereBoxCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereBoxCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
