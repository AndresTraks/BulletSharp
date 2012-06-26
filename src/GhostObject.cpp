#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionWorld.h"
#include "Dispatcher.h"
#include "GhostObject.h"
#include "OverlappingPairCache.h"

#define Unmanaged static_cast<btGhostObject*>(_unmanaged)

GhostObject::GhostObject(btGhostObject* ghostObject)
: CollisionObject(ghostObject)
{
}

GhostObject::GhostObject()
: CollisionObject(new btPairCachingGhostObject())
{
}

#ifndef DISABLE_INTERNAL
void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy, BroadphaseProxy^ thisProxy)
{
	Unmanaged->addOverlappingObjectInternal(otherProxy->UnmanagedPointer, thisProxy->UnmanagedPointer);
}

void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy)
{
	Unmanaged->addOverlappingObjectInternal(otherProxy->UnmanagedPointer);
}
#endif

CollisionObject^ GhostObject::GetOverlappingObject(int index)
{
	return CollisionObject::GetManaged(Unmanaged->getOverlappingObject(index));

}

void GhostObject::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, CollisionWorld::RayResultCallback^ resultCallback)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	Unmanaged->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_unmanaged);

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

#ifndef DISABLE_INTERNAL
void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher, BroadphaseProxy^ thisProxy)
{
	Unmanaged->removeOverlappingObjectInternal(otherProxy->UnmanagedPointer, dispatcher->UnmanagedPointer, thisProxy->UnmanagedPointer);
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher)
{
	Unmanaged->removeOverlappingObjectInternal(otherProxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}
#endif

GhostObject^ GhostObject::Upcast(CollisionObject^ colObj)
{
	btGhostObject* obj = btGhostObject::upcast(colObj->UnmanagedPointer);
	
	if (obj == 0)
		return nullptr;

	return gcnew GhostObject(obj);
}

int GhostObject::NumOverlappingObjects::get()
{
	return Unmanaged->getNumOverlappingObjects();
}

AlignedCollisionObjectArray^ GhostObject::OverlappingPairs::get()
{
	return gcnew AlignedCollisionObjectArray(&Unmanaged->getOverlappingPairs());
}

btGhostObject* GhostObject::UnmanagedPointer::get()
{
	return (btGhostObject*) CollisionObject::UnmanagedPointer;
}


#undef Unmanaged
#define Unmanaged static_cast<btPairCachingGhostObject*>(_unmanaged)

PairCachingGhostObject::PairCachingGhostObject(btPairCachingGhostObject* ghostObject)
: GhostObject(ghostObject)
{
}

PairCachingGhostObject::PairCachingGhostObject()
: GhostObject(new btPairCachingGhostObject())
{
}

HashedOverlappingPairCache^ PairCachingGhostObject::OverlappingPairCache::get()
{
	return gcnew HashedOverlappingPairCache(Unmanaged->getOverlappingPairCache());
}

btPairCachingGhostObject* PairCachingGhostObject::UnmanagedPointer::get()
{
	return (btPairCachingGhostObject*) GhostObject::UnmanagedPointer;
}

GhostPairCallback::GhostPairCallback(btGhostPairCallback* ghostPairCallback)
: OverlappingPairCallback(ghostPairCallback)
{
}

GhostPairCallback::GhostPairCallback()
: OverlappingPairCallback(new btGhostPairCallback)
{
}

btGhostPairCallback* GhostPairCallback::UnmanagedPointer::get()
{
	return (btGhostPairCallback*)OverlappingPairCallback::UnmanagedPointer;
}

#endif
