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
	Unmanaged->addOverlappingObjectInternal(otherProxy->_unmanaged, thisProxy->_unmanaged);
}

void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy)
{
	Unmanaged->addOverlappingObjectInternal(otherProxy->_unmanaged);
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
	Unmanaged->removeOverlappingObjectInternal(otherProxy->_unmanaged, dispatcher->_unmanaged, thisProxy->_unmanaged);
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher)
{
	Unmanaged->removeOverlappingObjectInternal(otherProxy->_unmanaged, dispatcher->_unmanaged);
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
	ReturnCachedObjectGcnew(AlignedCollisionObjectArray, _overlappingPairs, &Unmanaged->getOverlappingPairs());
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
	btHashedOverlappingPairCache* cache = Unmanaged->getOverlappingPairCache();
	ReturnCachedObjectCast(HashedOverlappingPairCache, _overlappingPairCache, cache);
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
