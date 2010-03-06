#pragma once

#include "DefaultCollisionConfiguration.h"

namespace BulletSharp
{
	public ref class SoftBodyRigidBodyCollisionConfiguration : DefaultCollisionConfiguration
	{
	public:
		SoftBodyRigidBodyCollisionConfiguration();

	internal:
		property btSoftBodyRigidBodyCollisionConfiguration* UnmanagedPointer
		{
			btSoftBodyRigidBodyCollisionConfiguration* get() new;
		}
	};
};
