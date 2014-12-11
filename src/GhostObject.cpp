#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "ConvexShape.h"
#include "Dispatcher.h"
#include "GhostObject.h"
#include "OverlappingPairCache.h"

#define Native static_cast<btGhostObject*>(_native)

GhostObject::GhostObject(btGhostObject* native)
	: CollisionObject(native)
{
}

GhostObject::GhostObject()
	: CollisionObject(new btGhostObject())
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

void GhostObject::ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld,
	Matrix convexToWorld, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration)
{
	TRANSFORM_CONV(convexFromWorld);
	TRANSFORM_CONV(convexToWorld);
	Native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(convexFromWorld),
		TRANSFORM_USE(convexToWorld), *resultCallback->_native, allowedCcdPenetration);
	TRANSFORM_DEL(convexFromWorld);
	TRANSFORM_DEL(convexToWorld);
}

void GhostObject::ConvexSweepTest(ConvexShape^ castShape, Matrix convexFromWorld,
	Matrix convexToWorld, ConvexResultCallback^ resultCallback)
{
	TRANSFORM_CONV(convexFromWorld);
	TRANSFORM_CONV(convexToWorld);
	Native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(convexFromWorld),
		TRANSFORM_USE(convexToWorld), *resultCallback->_native);
	TRANSFORM_DEL(convexFromWorld);
	TRANSFORM_DEL(convexToWorld);
}

CollisionObject^ GhostObject::GetOverlappingObject(int index)
{
	return CollisionObject::GetManaged(Native->getOverlappingObject(index));
}

void GhostObject::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback)
{
	VECTOR3_CONV(rayFromWorld);
	VECTOR3_CONV(rayToWorld);
	Native->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_native);
	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

#ifndef DISABLE_INTERNAL
void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher,
	BroadphaseProxy^ thisProxy)
{
	Native->removeOverlappingObjectInternal(otherProxy->_native, dispatcher->_native,
		thisProxy->_native);
}

void GhostObject::RemoveOverlappingObjectInternal(BroadphaseProxy^ otherProxy, Dispatcher^ dispatcher)
{
	Native->removeOverlappingObjectInternal(otherProxy->_native, dispatcher->_native);
}
#endif

GhostObject^ GhostObject::Upcast(CollisionObject^ colObj)
{
	btGhostObject* obj = btGhostObject::upcast(colObj->_native);
	return (GhostObject^) CollisionObject::GetManaged(obj);
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

PairCachingGhostObject::PairCachingGhostObject(btPairCachingGhostObject* native)
	: GhostObject(native)
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


GhostPairCallback::GhostPairCallback(btGhostPairCallback* native)
	: OverlappingPairCallback(native, true)
{
}

GhostPairCallback::GhostPairCallback()
	: OverlappingPairCallback(new btGhostPairCallback(), false)
{
}

#endif
