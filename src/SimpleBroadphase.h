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
		virtual BroadphaseProxy^ CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
			BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy) override;
		bool TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
	};
};
