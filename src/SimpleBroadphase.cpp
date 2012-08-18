#include "StdAfx.h"

#include "OverlappingPairCache.h"
#include "SimpleBroadphase.h"

SimpleBroadphaseProxy::SimpleBroadphaseProxy(btSimpleBroadphaseProxy* proxy)
: BroadphaseProxy(proxy)
{
}

SimpleBroadphaseProxy::SimpleBroadphaseProxy()
: BroadphaseProxy(new btSimpleBroadphaseProxy())
{
}

SimpleBroadphaseProxy::SimpleBroadphaseProxy(Vector3 minpt, Vector3 maxpt,
	int shapeType, Object^ userObject, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, IntPtr multiSapProxy)
: BroadphaseProxy(0)
{
	VECTOR3_DEF(minpt);
	VECTOR3_DEF(maxpt);

	_clientObject = userObject;

	UnmanagedPointer = new btSimpleBroadphaseProxy(VECTOR3_USE(minpt), VECTOR3_USE(maxpt), shapeType, 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask, multiSapProxy.ToPointer());

	VECTOR3_DEL(minpt);
	VECTOR3_DEL(maxpt);
}

int SimpleBroadphaseProxy::NextFree::get()
{
	return UnmanagedPointer->GetNextFree();
}
void SimpleBroadphaseProxy::NextFree::set(int value)
{
	UnmanagedPointer->SetNextFree(value);
}

btSimpleBroadphaseProxy* SimpleBroadphaseProxy::UnmanagedPointer::get()
{
	return (btSimpleBroadphaseProxy*)BroadphaseProxy::UnmanagedPointer;
}


#define Unmanaged static_cast<btSimpleBroadphase*>(_unmanaged)

SimpleBroadphase::SimpleBroadphase(btSimpleBroadphase* broadphase)
: BroadphaseInterface(broadphase)
{
}

SimpleBroadphase::SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache)
: BroadphaseInterface(new btSimpleBroadphase(maxProxies, (btOverlappingPairCache*)GetUnmanagedNullable(overlappingPairCache)))
{
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
	return Unmanaged->aabbOverlap(proxy0->UnmanagedPointer, proxy1->UnmanagedPointer);
}

bool SimpleBroadphase::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return Unmanaged->testAabbOverlap(proxy0->UnmanagedPointer, proxy1->UnmanagedPointer);
}
