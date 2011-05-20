#pragma once

#include "BroadphaseInterface.h"

namespace BulletSharp
{
	ref class OverlappingPairCache;

	public ref class AxisSweep3 : BroadphaseInterface
	{
	public:
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax);

	internal:
		property btAxisSweep3* UnmanagedPointer
		{
			btAxisSweep3* get() new;
		}
	};

	public ref class AxisSweep3_32Bit : BroadphaseInterface
	{
	public:
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax);

	internal:
		property bt32BitAxisSweep3* UnmanagedPointer
		{
			bt32BitAxisSweep3* get() new;
		}
	};
};
