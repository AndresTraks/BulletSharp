#pragma once

namespace BulletSharp
{
	public ref class DefaultCollisionConfiguration : BulletSharp::CollisionConfiguration
	{
		public:
			DefaultCollisionConfiguration();
			void SetConvexConvexMultipointIterations(int numPerturbationIterations);
			void SetConvexConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);

		internal:
			property btDefaultCollisionConfiguration* UnmanagedPointer
			{
				btDefaultCollisionConfiguration* get() new;
			}
	};
};
