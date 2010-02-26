#pragma once

#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class CollisionDispatcher : Dispatcher
	{
		public:
			CollisionDispatcher(CollisionConfiguration^ collisionConfiguration);
			CollisionDispatcher();

			void RegisterCollisionCreateFunc(BroadphaseNativeTypes proxyType0,
				BroadphaseNativeTypes proxyType1,
				CollisionAlgorithmCreateFunc^ createFunc);

			property btCollisionDispatcher* UnmanagedPointer
			{
				virtual btCollisionDispatcher* get() new;
			}
	};
};
