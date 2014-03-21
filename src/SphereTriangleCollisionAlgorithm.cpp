#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "PersistentManifold.h"
#include "SphereTriangleCollisionAlgorithm.h"

SphereTriangleCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btSphereTriangleCollisionAlgorithm::CreateFunc())
{
}


SphereTriangleCollisionAlgorithm::SphereTriangleCollisionAlgorithm(PersistentManifold^ mf,
	CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	bool swapped)
	: ActivatingCollisionAlgorithm(new btSphereTriangleCollisionAlgorithm((btPersistentManifold*)GetUnmanagedNullable(mf),
		*ci->_native, body0Wrap->_native, body1Wrap->_native, swapped))
{
}

SphereTriangleCollisionAlgorithm::SphereTriangleCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci)
	: ActivatingCollisionAlgorithm(new btSphereTriangleCollisionAlgorithm(*ci->_native))
{
}

#endif
