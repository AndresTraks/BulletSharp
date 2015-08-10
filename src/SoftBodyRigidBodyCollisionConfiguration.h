#pragma once

#include "DefaultCollisionConfiguration.h"

namespace BulletSharp
{
	public ref class SoftBodyRigidBodyCollisionConfiguration : DefaultCollisionConfiguration
	{
	public:
		SoftBodyRigidBodyCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo);
		SoftBodyRigidBodyCollisionConfiguration();

		virtual CollisionAlgorithmCreateFunc^ GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1) override;
	};
};
