#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

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
