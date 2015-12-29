#include "StdAfx.h"

#include "AxisSweep3.h"
#include "BroadphaseProxy.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "OverlappingPairCallback.h"

#define Native static_cast<btAxisSweep3*>(_native)

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
	BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles, (btOverlappingPairCache*)GetUnmanagedNullable(pairCache), disableRaycastAccelerator);
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = pairCache ? pairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
	 BulletSharp::OverlappingPairCache^ pairCache)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles, (btOverlappingPairCache*)GetUnmanagedNullable(pairCache));
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = pairCache ? pairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles);
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3::AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new btAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

unsigned short AxisSweep3::AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	unsigned short ret = Native->addHandle(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), pOwner.ToPointer(),
		collisionFilterGroup, collisionFilterMask, dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return ret;
}

unsigned short AxisSweep3::AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	unsigned short ret = Native->addHandle(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), pOwner.ToPointer(),
		(short)collisionFilterGroup, (short)collisionFilterMask, dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return ret;
}

BroadphaseProxy^ AxisSweep3::CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
	BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btBroadphaseProxy* proxy = _native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		(int)shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return gcnew BroadphaseProxy(proxy);
}
/*
Handle^ AxisSweep3::GetHandle(unsigned short index)
{
	return Native->getHandle(index->_native);
}

void AxisSweep3::ProcessAllOverlappingPairs(OverlapCallback^ callback)
{
	Native->processAllOverlappingPairs(callback->_native);
}
*/
void AxisSweep3::Quantize([Out] unsigned short% out, Vector3 point, int isMax)
{
	VECTOR3_CONV(point);
	unsigned short outTemp;
	Native->quantize(&outTemp, VECTOR3_USE(point), isMax);
	out = outTemp;
	VECTOR3_DEL(point);
}

void AxisSweep3::RemoveHandle(unsigned short handle, Dispatcher^ dispatcher)
{
	Native->removeHandle(handle, dispatcher->_native);
}

bool AxisSweep3::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return Native->testAabbOverlap(proxy0->_native, proxy1->_native);
}

void AxisSweep3::UnQuantize(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->unQuantize(proxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void AxisSweep3::UpdateHandle(unsigned short handle, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->updateHandle(handle, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

unsigned short AxisSweep3::NumHandles::get()
{
	return Native->getNumHandles();
}

OverlappingPairCallback^ AxisSweep3::OverlappingPairUserCallback::get()
{
	return _overlappingPairUserCallback;
}
void AxisSweep3::OverlappingPairUserCallback::set(OverlappingPairCallback^ pairCallback)
{
	_overlappingPairUserCallback = pairCallback;
	Native->setOverlappingPairUserCallback(GetUnmanagedNullable(pairCallback));
}


#undef Native
#define Native static_cast<bt32BitAxisSweep3*>(_native)

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
	BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles, (btOverlappingPairCache*)pairCache->_native, disableRaycastAccelerator);
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = pairCache ? pairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
	BulletSharp::OverlappingPairCache^ pairCache)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles, (btOverlappingPairCache*)pairCache->_native);
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = pairCache ? pairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax),
		maxHandles);
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

AxisSweep3_32Bit::AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax)
	: BroadphaseInterface(0)
{
	VECTOR3_CONV(worldAabbMin);
	VECTOR3_CONV(worldAabbMax);
	_native = new bt32BitAxisSweep3(VECTOR3_USE(worldAabbMin), VECTOR3_USE(worldAabbMax));
	VECTOR3_DEL(worldAabbMin);
	VECTOR3_DEL(worldAabbMax);

	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

unsigned int AxisSweep3_32Bit::AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	unsigned int ret = Native->addHandle(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), pOwner.ToPointer(),
		collisionFilterGroup, collisionFilterMask, dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return ret;
}

unsigned int AxisSweep3_32Bit::AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	unsigned int ret = Native->addHandle(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), pOwner.ToPointer(),
		(short)collisionFilterGroup, (short)collisionFilterMask, dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return ret;
}

BroadphaseProxy^ AxisSweep3_32Bit::CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
	BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btBroadphaseProxy* proxy = _native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		(int)shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return gcnew BroadphaseProxy(proxy);
}
/*
Handle^ AxisSweep3_32Bit::GetHandle(unsigned short index)
{
	return Native->getHandle(index->_native);
}

void AxisSweep3_32Bit::ProcessAllOverlappingPairs(OverlapCallback^ callback)
{
	Native->processAllOverlappingPairs(callback->_native);
}
*/
void AxisSweep3_32Bit::Quantize([Out] unsigned int% out, Vector3 point, int isMax)
{
	VECTOR3_CONV(point);
	unsigned int outTemp;
	Native->quantize(&outTemp, VECTOR3_USE(point), isMax);
	out = outTemp;
	VECTOR3_DEL(point);
}

void AxisSweep3_32Bit::RemoveHandle(unsigned int handle, Dispatcher^ dispatcher)
{
	Native->removeHandle(handle, dispatcher->_native);
}

bool AxisSweep3_32Bit::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return Native->testAabbOverlap(proxy0->_native, proxy1->_native);
}

void AxisSweep3_32Bit::UnQuantize(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->unQuantize(proxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void AxisSweep3_32Bit::UpdateHandle(unsigned int handle, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->updateHandle(handle, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

unsigned int AxisSweep3_32Bit::NumHandles::get()
{
	return Native->getNumHandles();
}

OverlappingPairCallback^ AxisSweep3_32Bit::OverlappingPairUserCallback::get()
{
	return _overlappingPairUserCallback;
}
void AxisSweep3_32Bit::OverlappingPairUserCallback::set(OverlappingPairCallback^ pairCallback)
{
	_overlappingPairUserCallback = pairCallback;
	Native->setOverlappingPairUserCallback(GetUnmanagedNullable(pairCallback));
}
