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
	int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, IntPtr multiSapProxy)
: BroadphaseProxy(new btSimpleBroadphaseProxy(*Math::Vector3ToBtVector3(minpt),
	*Math::Vector3ToBtVector3(maxpt), shapeType, userPtr.ToPointer(),
	(short int)collisionFilterGroup, (short int)collisionFilterMask,
	multiSapProxy.ToPointer()))
{
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


SimpleBroadphase::SimpleBroadphase(int maxProxies, BulletSharp::OverlappingPairCache^ overlappingPairCache)
: BroadphaseInterface(new btSimpleBroadphase(maxProxies, overlappingPairCache->UnmanagedPointer))
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
	return UnmanagedPointer->aabbOverlap(proxy0->UnmanagedPointer, proxy1->UnmanagedPointer);
}

bool SimpleBroadphase::TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	return UnmanagedPointer->testAabbOverlap(proxy0->UnmanagedPointer, proxy1->UnmanagedPointer);
}

btSimpleBroadphase* SimpleBroadphase::UnmanagedPointer::get()
{
	return (btSimpleBroadphase*)BroadphaseInterface::UnmanagedPointer;
}
