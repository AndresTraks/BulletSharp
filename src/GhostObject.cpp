#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionWorld.h"
#include "Dispatcher.h"
#include "GhostObject.h"
#include "OverlappingPairCache.h"

#define Native static_cast<btGhostObject*>(_native)

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
	Native->addOverlappingObjectInternal(otherProxy->_native, thisProxy->_native);
}

void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy)
{
	Native->addOverlappingObjectInternal(otherProxy->_native);
}
#endif

CollisionObject^ GhostObject::GetOverlappingObject(int index)
{
	return CollisionObject::GetManaged(Native->getOverlappingObject(index));

}

void GhostObject::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, CollisionWorld::RayResultCallback^ resultCallback)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	Native->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_native);

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

#ifndef DISABLE_INTERNAL
void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher, BroadphaseProxy^ thisProxy)
{
	Native->removeOverlappingObjectInternal(otherProxy->_native, dispatcher->_native, thisProxy->_native);
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher)
{
	Native->removeOverlappingObjectInternal(otherProxy->_native, dispatcher->_native);
}
#endif

GhostObject^ GhostObject::Upcast(CollisionObject^ colObj)
{
	btGhostObject* obj = btGhostObject::upcast(colObj->_native);
	
	if (obj == 0)
		return nullptr;

	return gcnew GhostObject(obj);
}

int GhostObject::NumOverlappingObjects::get()
{
	return Native->getNumOverlappingObjects();
}

AlignedCollisionObjectArray^ GhostObject::OverlappingPairs::get()
{
	ReturnCachedObjectGcnew(AlignedCollisionObjectArray, _overlappingPairs, &Native->getOverlappingPairs());
}


#undef Native
#define Native static_cast<btPairCachingGhostObject*>(_native)

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
	btHashedOverlappingPairCache* cache = Native->getOverlappingPairCache();
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

#endif
