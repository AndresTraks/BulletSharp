#pragma once

#include "BroadphaseInterface.h"

namespace BulletSharp
{
	ref class OverlappingPairCache;

	public ref class AxisSweep3 : BroadphaseInterface
	{
	internal:
		AxisSweep3(btAxisSweep3* native);

	public:
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax);
	};

	public ref class AxisSweep3_32Bit : BroadphaseInterface
	{
	internal:
		AxisSweep3_32Bit(bt32BitAxisSweep3* native);

	public:
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax);
	};
};
