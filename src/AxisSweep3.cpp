#include "StdAfx.h"

#include "AxisSweep3.h"
#include "OverlappingPairCache.h"

AxisSweep3::AxisSweep3(btAxisSweep3* axisSweep)
	: BroadphaseInterface(axisSweep)
{
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, (btOverlappingPairCache*)pairCache->_native, disableRaycastAccelerator);
	_pairCache = pairCache;

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, (btOverlappingPairCache*)pairCache->_native);
	_pairCache = pairCache;

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}


AxisSweep3_32Bit::AxisSweep3_32Bit(bt32BitAxisSweep3* axisSweep)
	: BroadphaseInterface(axisSweep)
{
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, (btOverlappingPairCache*)pairCache->_native, disableRaycastAccelerator);
	_pairCache = pairCache;

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles, BulletSharp::OverlappingPairCache^ pairCache)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles, (btOverlappingPairCache*)pairCache->_native);
	_pairCache = pairCache;

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, int maxHandles)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax), maxHandles);

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax)
	: BroadphaseInterface(0)
{
	VECTOR3_DEF(worldAabbMin);
	VECTOR3_DEF(worldAabbMax);

	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));

	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);
}
