#include "StdAfx.h"

#include "AxisSweep3.h"
#include "OverlappingPairCache.h"

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, pairCache->UnmanagedPointer, disableRaycastAccelerator);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, pairCache->UnmanagedPointer);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

btAxisSweep3* AxisSweep3::UnmanagedPointer::get()
{
	return (btAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}


AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, pairCache->UnmanagedPointer, disableRaycastAccelerator);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, pairCache->UnmanagedPointer);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

bt32BitAxisSweep3* AxisSweep3_32Bit::UnmanagedPointer::get()
{
	return (bt32BitAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}
