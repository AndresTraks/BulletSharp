#include "StdAfx.h"

#include "AxisSweep3.h"
#include "OverlappingPairCache.h"

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(new btAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles,
	pairCache->UnmanagedPointer,
	disableRaycastAccelerator))
{
	_pairCache = pairCache;
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(new btAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles,
	pairCache->UnmanagedPointer))
{
	_pairCache = pairCache;
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(new btAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles))
{
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(new btAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax)
	))
{
}

btAxisSweep3* AxisSweep3::UnmanagedPointer::get()
{
	return (btAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}


AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
: BroadphaseInterface(new bt32BitAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles,
	pairCache->UnmanagedPointer,
	disableRaycastAccelerator))
{
	_pairCache = pairCache;
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
: BroadphaseInterface(new bt32BitAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles,
	pairCache->UnmanagedPointer))
{
	_pairCache = pairCache;
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
: BroadphaseInterface(new bt32BitAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax),
	maxHandles))
{
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax)
: BroadphaseInterface(new bt32BitAxisSweep3(
	*Math::Vector3ToBtVector3(worldAabbMin),
	*Math::Vector3ToBtVector3(worldAabbMax)
	))
{
}

bt32BitAxisSweep3* AxisSweep3_32Bit::UnmanagedPointer::get()
{
	return (bt32BitAxisSweep3*)BroadphaseInterface::UnmanagedPointer;
}
