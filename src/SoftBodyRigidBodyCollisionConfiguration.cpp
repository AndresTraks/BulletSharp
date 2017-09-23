#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "SoftBodyRigidBodyCollisionConfiguration.h"

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration(
	DefaultCollisionConstructionInfo^ constructionInfo)
	: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration(*constructionInfo->_native),
#ifndef DISABLE_UNCOMMON
		constructionInfo->CollisionAlgorithmPool, constructionInfo->PersistentManifoldPool)
#else
	nullptr, nullptr)
#endif
{
}

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration()
	: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration(), nullptr, nullptr)
{
}

#ifndef DISABLE_COLLISION_ALGORITHMS
CollisionAlgorithmCreateFunc^ SoftBodyRigidBodyCollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	// TODO

	return DefaultCollisionConfiguration::GetCollisionAlgorithmCreateFunc(proxyType0, proxyType1);
}
#endif

#endif
