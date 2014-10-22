#include "StdAfx.h"

#include "OverlappingPairCache.h"
#include "SimpleBroadphase.h"

#define Native static_cast<btSimpleBroadphaseProxy*>(_native)

SimpleBroadphaseProxy::SimpleBroadphaseProxy(btSimpleBroadphaseProxy* native)
	: BroadphaseProxy(native, false)
{
}

SimpleBroadphaseProxy::SimpleBroadphaseProxy()
	: BroadphaseProxy(new btSimpleBroadphaseProxy(), false)
{
}

SimpleBroadphaseProxy::SimpleBroadphaseProxy(Vector3 minpt, Vector3 maxpt, int shapeType,
	Object^ userObject, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask, IntPtr multiSapProxy)
	: BroadphaseProxy(0, false)
{
	_clientObject = userObject;

	VECTOR3_CONV(minpt);
	VECTOR3_CONV(maxpt);
	UnmanagedPointer = new btSimpleBroadphaseProxy(VECTOR3_USE(minpt), VECTOR3_USE(maxpt),
		shapeType, 0, (short int)collisionFilterGroup, (short int)collisionFilterMask, multiSapProxy.ToPointer());
	VECTOR3_DEL(minpt);
	VECTOR3_DEL(maxpt);
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

SimpleBroadphase::SimpleBroadphase(btSimpleBroadphase* native)
	: BroadphaseInterface(native)
{
}

SimpleBroadphase::SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache)
	: BroadphaseInterface(new btSimpleBroadphase(maxProxies, (btOverlappingPairCache*)GetUnmanagedNullable(overlappingPairCache)))
{
	_pairCache = overlappingPairCache;
}

SimpleBroadphase::SimpleBroadphase(int maxProxies)
	: BroadphaseInterface(new btSimpleBroadphase(maxProxies))
{
}

SimpleBroadphase::SimpleBroadphase()
	: BroadphaseInterface(new btSimpleBroadphase())
{
}

bool SimpleBroadphase::AabbOverlap(SimpleBroadphaseProxy^ proxy0, SimpleBroadphaseProxy^ proxy1)
{
	return btSimpleBroadphase::aabbOverlap((btSimpleBroadphaseProxy*)proxy0->_native,
		(btSimpleBroadphaseProxy*)proxy1->_native);
}

bool SimpleBroadphase::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return Native->testAabbOverlap((btSimpleBroadphaseProxy*)proxy0->_native, (btSimpleBroadphaseProxy*)proxy1->_native);
}
