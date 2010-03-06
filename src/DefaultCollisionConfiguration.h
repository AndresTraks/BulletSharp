#pragma once

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	public ref class DefaultCollisionConfiguration : CollisionConfiguration
	{
	internal:
		DefaultCollisionConfiguration(btDefaultCollisionConfiguration* conf);
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
