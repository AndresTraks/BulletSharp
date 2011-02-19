#include "StdAfx.h"

#include "AxisSweep3.h"
#include "OverlappingPairCache.h"

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles, pairCache->UnmanagedPointer, disableRaycastAccelerator);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles, pairCache->UnmanagedPointer);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new btAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

btAxisSweep3* AxisSweep3::UnmanagedPointer::get()
{
	return (btAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}


AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles, pairCache->UnmanagedPointer, disableRaycastAccelerator);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles, pairCache->UnmanagedPointer);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp, maxHandles);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(0)
{
	btVector3* worldAabbMinTemp = Math::Vector3ToBtVector3(worldAabbMin);
	btVector3* worldAabbMaxTemp = Math::Vector3ToBtVector3(worldAabbMax);

	UnmanagedPointer = new bt32BitAxisSweep3(*worldAabbMinTemp, *worldAabbMaxTemp);

	delete worldAabbMinTemp;
	delete worldAabbMaxTemp;
}

bt32BitAxisSweep3* AxisSweep3_32Bit::UnmanagedPointer::get()
{
	return (bt32BitAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}
