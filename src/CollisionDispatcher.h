#pragma once

namespace BulletSharp
{
	public ref class CollisionDispatcher : IDispatcher
	{
		private:
			btCollisionDispatcher* _dispatcher;

		public:
			CollisionDispatcher(CollisionConfiguration^ collisionConfiguration);
			CollisionDispatcher();

			property btDispatcher* UnmanagedPointer
			{
				virtual btDispatcher* get();
			}
	};
};
