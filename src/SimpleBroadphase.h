#pragma once

// Fully implemented as of 10 Mar 2010

#include "BroadphaseInterface.h"
#include "BroadphaseProxy.h"

namespace BulletSharp
{
	ref class OverlappingPairCache;

	public ref class SimpleBroadphaseProxy : BroadphaseProxy
	{
	internal:
		SimpleBroadphaseProxy(btSimpleBroadphaseProxy* proxy);

	public:
		SimpleBroadphaseProxy();
		SimpleBroadphaseProxy(Vector3 minpt, Vector3 maxpt,
			int shapeType, IntPtr userPtr,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask,
			IntPtr multiSapProxy);

		property int NextFree
		{
			int get();
			void set(int value);
		}

		property btSimpleBroadphaseProxy* UnmanagedPointer
		{
			btSimpleBroadphaseProxy* get() new;
		}
	};

	public ref class SimpleBroadphase : BroadphaseInterface
	{
	public:
		SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache);
		SimpleBroadphase(int maxProxies);
		SimpleBroadphase();

		bool AabbOverlap(SimpleBroadphaseProxy^ proxy0, SimpleBroadphaseProxy^ proxy1);
		bool TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);

	internal:
		property btSimpleBroadphase* UnmanagedPointer
		{
			btSimpleBroadphase* get() new;
		}
	};
};
