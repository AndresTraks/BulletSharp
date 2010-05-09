#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionWorld.h"
#include "Dispatcher.h"
#include "GhostObject.h"
#include "OverlappingPairCache.h"

GhostObject::GhostObject(btGhostObject* ghostObject)
: CollisionObject(ghostObject)
{
}

GhostObject::GhostObject()
: CollisionObject(new btPairCachingGhostObject())
{
}

void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy, BroadphaseProxy^ thisProxy)
{
	UnmanagedPointer->addOverlappingObjectInternal(otherProxy->UnmanagedPointer, thisProxy->UnmanagedPointer);
}

void GhostObject::AddOverlappingObjectInternal(BroadphaseProxy^ otherProxy)
{
	UnmanagedPointer->addOverlappingObjectInternal(otherProxy->UnmanagedPointer);
}

CollisionObject^ GhostObject::GetOverlappingObject(int index)
{
	return gcnew CollisionObject(UnmanagedPointer->getOverlappingObject(index));

}

void GhostObject::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, CollisionWorld::RayResultCallback^ resultCallback)
{
	btVector3* rayFromWorldTemp = Math::Vector3ToBtVector3(rayFromWorld);
	btVector3* rayToWorldTemp = Math::Vector3ToBtVector3(rayToWorld);

	UnmanagedPointer->rayTest(*rayFromWorldTemp, *rayToWorldTemp, *resultCallback->UnmanagedPointer);

	delete rayFromWorldTemp;
	delete rayToWorldTemp;
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher, BroadphaseProxy^ thisProxy)
{
	UnmanagedPointer->removeOverlappingObjectInternal(otherProxy->UnmanagedPointer, dispatcher->UnmanagedPointer, thisProxy->UnmanagedPointer);
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher)
{
	UnmanagedPointer->removeOverlappingObjectInternal(otherProxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

GhostObject^ GhostObject::Upcast(CollisionObject^ colObj)
{
	btGhostObject* obj = btGhostObject::upcast(colObj->UnmanagedPointer);
	
	if (obj = 0)
		return nullptr;

	return gcnew GhostObject(obj);
}

int GhostObject::NumOverlappingObjects::get()
{
	return UnmanagedPointer->getNumOverlappingObjects();
}

CollisionObjectArray^ GhostObject::OverlappingPairs::get()
{
	return gcnew CollisionObjectArray(&UnmanagedPointer->getOverlappingPairs());
}

btGhostObject* GhostObject::UnmanagedPointer::get()
{
	return (btGhostObject*) CollisionObject::UnmanagedPointer;
}


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
	return gcnew HashedOverlappingPairCache(UnmanagedPointer->getOverlappingPairCache());
}

btPairCachingGhostObject* PairCachingGhostObject::UnmanagedPointer::get()
{
	return (btPairCachingGhostObject*) GhostObject::UnmanagedPointer;
}
