#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "SoftBodyRigidBodyCollisionConfiguration.h"

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo)
	: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration(*constructionInfo->_native))
{
}

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration()
	: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration())
{
}

CollisionAlgorithmCreateFunc^ SoftBodyRigidBodyCollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	// TODO

	return DefaultCollisionConfiguration::GetCollisionAlgorithmCreateFunc(proxyType0, proxyType1);
}

#endif
