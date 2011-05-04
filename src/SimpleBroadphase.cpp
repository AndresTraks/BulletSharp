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
	btVector3* minptTemp = Math::Vector3ToBtVector3(minpt);
	btVector3* maxptTemp = Math::Vector3ToBtVector3(maxpt);

	_clientObject = userObject;

	UnmanagedPointer = new btSimpleBroadphaseProxy(*minptTemp, *maxptTemp, shapeType, 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask, multiSapProxy.ToPointer());

	delete minptTemp;
	delete maxptTemp;
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
: BroadphaseInterface(new btSimpleBroadphase(maxProxies, GetUnmanagedNullable(overlappingPairCache)))
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
