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

#endif
