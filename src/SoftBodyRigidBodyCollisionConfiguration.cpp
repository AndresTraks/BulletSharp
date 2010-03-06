#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#pragma managed(pop)

#include "SoftBodyRigidBodyCollisionConfiguration.h"

SoftBodyRigidBodyCollisionConfiguration::SoftBodyRigidBodyCollisionConfiguration()
: DefaultCollisionConfiguration(new btSoftBodyRigidBodyCollisionConfiguration())
{
}

btSoftBodyRigidBodyCollisionConfiguration* SoftBodyRigidBodyCollisionConfiguration::UnmanagedPointer::get()
{
	return (btSoftBodyRigidBodyCollisionConfiguration*)DefaultCollisionConfiguration::UnmanagedPointer;
}

#endif
