#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "SoftBodyRigidBodyCollisionConfiguration.h"

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration()
: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration())
{
}

#endif
