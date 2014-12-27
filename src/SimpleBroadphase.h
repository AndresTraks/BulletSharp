#pragma once

#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"

namespace BulletSharp
{
	ref class OverlappingPairCache;

	public ref class SimpleBroadphaseProxy : BroadphaseProxy
	{
	internal:
		SimpleBroadphaseProxy(btSimpleBroadphaseProxy* native);

	public:
		/*
		SimpleBroadphaseProxy();
		SimpleBroadphaseProxy(Vector3 minpt, Vector3 maxpt, int shapeType, Object^ userObject,
			CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask, IntPtr multiSapProxy);
		*/

		property int NextFree
		{
			int get();
			void set(int next);
		}
	};

	public ref class SimpleBroadphase : BroadphaseInterface
	{
	public:
		SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache);
		SimpleBroadphase(int maxProxies);
		SimpleBroadphase();

		static bool AabbOverlap(SimpleBroadphaseProxy^ proxy0, SimpleBroadphaseProxy^ proxy1);
		bool TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
	};
};
