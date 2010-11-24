#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "PersistentManifold.h"
#include "SphereBoxCollisionAlgorithm.h"

SphereBoxCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSphereBoxCollisionAlgorithm::CreateFunc())
{
}

SphereBoxCollisionAlgorithm::SphereBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1, bool isSwapped)
: ActivatingCollisionAlgorithm(new btSphereBoxCollisionAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer,
	body0->UnmanagedPointer, body1->UnmanagedPointer, isSwapped))
{
}

btScalar SphereBoxCollisionAlgorithm::GetSphereDistance(CollisionObject^ boxObj, Vector3 v3PointOnBox,
	Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius)
{
	btVector3* v3PointOnBoxTemp = Math::Vector3ToBtVector3(v3PointOnBox);
	btVector3* v3PointOnSphereTemp = Math::Vector3ToBtVector3(v3PointOnSphere);
	btVector3* v3SphereCenterTemp = Math::Vector3ToBtVector3(v3SphereCenter);

	btScalar ret = UnmanagedPointer->getSphereDistance(boxObj->UnmanagedPointer, *v3PointOnBoxTemp, *v3PointOnSphereTemp,
		*v3SphereCenterTemp, fRadius);

	delete v3PointOnBoxTemp;
	delete v3PointOnSphereTemp;
	delete v3SphereCenterTemp;

	return ret;
}

btScalar SphereBoxCollisionAlgorithm::GetSpherePenetration(CollisionObject^ boxObj, Vector3 v3PointOnBox,
	Vector3 v3PointOnSphere, Vector3 v3SphereCenter, btScalar fRadius, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* v3PointOnBoxTemp = Math::Vector3ToBtVector3(v3PointOnBox);
	btVector3* v3PointOnSphereTemp = Math::Vector3ToBtVector3(v3PointOnSphere);
	btVector3* v3SphereCenterTemp = Math::Vector3ToBtVector3(v3SphereCenter);
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	btScalar ret = UnmanagedPointer->getSpherePenetration(boxObj->UnmanagedPointer, *v3PointOnBoxTemp, *v3PointOnSphereTemp,
		*v3SphereCenterTemp, fRadius, *aabbMinTemp, *aabbMaxTemp);

	delete v3PointOnBoxTemp;
	delete v3PointOnSphereTemp;
	delete v3SphereCenterTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;

	return ret;
}

btSphereBoxCollisionAlgorithm* SphereBoxCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereBoxCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
