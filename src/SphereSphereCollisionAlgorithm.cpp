#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"
#include "SphereSphereCollisionAlgorithm.h"

SphereSphereCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btSphereSphereCollisionAlgorithm::CreateFunc())
{
}

SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm((btPersistentManifold*)GetUnmanagedNullable(mf), *ci->UnmanagedPointer,
	body0Wrap->_unmanaged, body1Wrap->_unmanaged))
{
}

SphereSphereCollisionAlgorithm::SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
: ActivatingCollisionAlgorithm(new btSphereSphereCollisionAlgorithm(*ci->UnmanagedPointer))
{
}

btSphereSphereCollisionAlgorithm* SphereSphereCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btSphereSphereCollisionAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
