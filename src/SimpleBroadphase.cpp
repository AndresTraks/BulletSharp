#include "StdAfx.h"

#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "SimpleBroadphase.h"

#define Native static_cast<btSimpleBroadphaseProxy*>(_native)

SimpleBroadphaseProxy::SimpleBroadphaseProxy(btSimpleBroadphaseProxy* native)
	: BroadphaseProxy(native)
{
}

int SimpleBroadphaseProxy::NextFree::get()
{
	return Native->GetNextFree();
}
void SimpleBroadphaseProxy::NextFree::set(int next)
{
	Native->SetNextFree(next);
}


#undef Native
#define Native static_cast<btSimpleBroadphase*>(_native)

SimpleBroadphase::SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache)
	: BroadphaseInterface(new btSimpleBroadphase(maxProxies, (btOverlappingPairCache*)GetUnmanagedNullable(overlappingPairCache)))
{
	_overlappingPairCache = overlappingPairCache ? overlappingPairCache : gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

SimpleBroadphase::SimpleBroadphase(int maxProxies)
	: BroadphaseInterface(new btSimpleBroadphase(maxProxies))
{
	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

SimpleBroadphase::SimpleBroadphase()
	: BroadphaseInterface(new btSimpleBroadphase())
{
	_overlappingPairCache = gcnew HashedOverlappingPairCache(
		(btHashedOverlappingPairCache*)_native->getOverlappingPairCache(), true);
}

bool SimpleBroadphase::AabbOverlap(SimpleBroadphaseProxy^ proxy0, SimpleBroadphaseProxy^ proxy1)
{
	return btSimpleBroadphase::aabbOverlap((btSimpleBroadphaseProxy*)proxy0->_native,
		(btSimpleBroadphaseProxy*)proxy1->_native);
}

BroadphaseProxy^ SimpleBroadphase::CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
	BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
	short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btSimpleBroadphaseProxy* proxy = (btSimpleBroadphaseProxy*)_native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		(int)shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return gcnew SimpleBroadphaseProxy(proxy);
}

bool SimpleBroadphase::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return Native->testAabbOverlap((btSimpleBroadphaseProxy*)proxy0->_native, (btSimpleBroadphaseProxy*)proxy1->_native);
}
