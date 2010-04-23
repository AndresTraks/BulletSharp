#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CollisionWorld.h"
#include "ConvexShape.h"
#include "Dispatcher.h"
#include "ManifoldPoint.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

int CollisionWorld::LocalShapeInfo::ShapePart::get()
{
	return _info->m_shapePart;
}
void CollisionWorld::LocalShapeInfo::ShapePart::set(int value)
{
	_info->m_shapePart = value;
}

int CollisionWorld::LocalShapeInfo::TriangleIndex::get()
{
	return _info->m_triangleIndex;
}
void CollisionWorld::LocalShapeInfo::TriangleIndex::set(int value)
{
	_info->m_triangleIndex = value;
}


CollisionWorld::LocalConvexResult::LocalConvexResult(BulletSharp::CollisionObject^ collisionObject, CollisionWorld::LocalShapeInfo^ localShapeInfo,
	Vector3 hitNormalLocal, Vector3 hitPointLocal, btScalar hitFraction)
{
	_result = new btCollisionWorld::LocalConvexResult(collisionObject->UnmanagedPointer, localShapeInfo->UnmanagedPointer,
		*Math::Vector3ToBtVector3(hitNormalLocal), *Math::Vector3ToBtVector3(hitPointLocal), hitFraction);
}

BulletSharp::CollisionObject^ CollisionWorld::LocalConvexResult::CollisionObject::get()
{
	return gcnew BulletSharp::CollisionObject(_result->m_hitCollisionObject);
}
void CollisionWorld::LocalConvexResult::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_result->m_hitCollisionObject = value->UnmanagedPointer;
}

btScalar CollisionWorld::LocalConvexResult::HitFraction::get()
{
	return _result->m_hitFraction;
}
void CollisionWorld::LocalConvexResult::HitFraction::set(btScalar value)
{
	_result->m_hitFraction = value;
}

Vector3 CollisionWorld::LocalConvexResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_result->m_hitNormalLocal);
}
void CollisionWorld::LocalConvexResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_result->m_hitNormalLocal);
}

CollisionWorld::LocalShapeInfo^ CollisionWorld::LocalConvexResult::LocalShapeInfo::get()
{
	return gcnew CollisionWorld::LocalShapeInfo(_result->m_localShapeInfo);
}
void CollisionWorld::LocalConvexResult::LocalShapeInfo::set(CollisionWorld::LocalShapeInfo^ value)
{
	_result->m_localShapeInfo = value->UnmanagedPointer;
}

btCollisionWorld::LocalConvexResult* CollisionWorld::LocalConvexResult::UnmanagedPointer::get()
{
	return _result;
}
void CollisionWorld::LocalConvexResult::UnmanagedPointer::set(btCollisionWorld::LocalConvexResult* value)
{
	_result = value;
}


CollisionWorld::ConvexResultCallback::ConvexResultCallback(btCollisionWorld::ConvexResultCallback* callback)
{
	_callback = callback;
}

CollisionWorld::ConvexResultCallback::~ConvexResultCallback()
{
	this->!ConvexResultCallback();
}

CollisionWorld::ConvexResultCallback::!ConvexResultCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

btScalar CollisionWorld::ConvexResultCallback::AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace)
{
	return _callback->addSingleResult(*convexResult->UnmanagedPointer, normalInWorldSpace);
}

bool CollisionWorld::ConvexResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _callback->needsCollision(proxy0->UnmanagedPointer);
}

btScalar CollisionWorld::ConvexResultCallback::ClosestHitFraction::get()
{
	return _callback->m_closestHitFraction;
}
void CollisionWorld::ConvexResultCallback::ClosestHitFraction::set(btScalar value)
{
	_callback->m_closestHitFraction = value;
}

CollisionFilterGroups CollisionWorld::ConvexResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterGroup;
}
void CollisionWorld::ConvexResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::ConvexResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterMask;
}
void CollisionWorld::ConvexResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterMask = (short int)value;
}

bool CollisionWorld::ConvexResultCallback::HasHit::get()
{
	return _callback->hasHit();
}

bool CollisionWorld::ConvexResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btCollisionWorld::ConvexResultCallback* CollisionWorld::ConvexResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::ConvexResultCallback::UnmanagedPointer::set(btCollisionWorld::ConvexResultCallback* value)
{
	_callback = value;
}


CollisionWorld::ClosestConvexResultCallback::ClosestConvexResultCallback(btCollisionWorld::ClosestConvexResultCallback* callback)
: ConvexResultCallback(callback)
{
}

CollisionWorld::ClosestConvexResultCallback::ClosestConvexResultCallback(Vector3 convexFromWorld, Vector3 convexToWorld)
: ConvexResultCallback(new btCollisionWorld::ClosestConvexResultCallback(
	*Math::Vector3ToBtVector3(convexFromWorld), *Math::Vector3ToBtVector3(convexToWorld)))
{
}

BulletSharp::CollisionObject^ CollisionWorld::ClosestConvexResultCallback::CollisionObject::get()
{
	return gcnew BulletSharp::CollisionObject(UnmanagedPointer->m_hitCollisionObject);
}
void CollisionWorld::ClosestConvexResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	UnmanagedPointer->m_hitCollisionObject = value->UnmanagedPointer;
}

Vector3 CollisionWorld::ClosestConvexResultCallback::ConvexFromWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_convexFromWorld);
}
void CollisionWorld::ClosestConvexResultCallback::ConvexFromWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_convexFromWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::ConvexToWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_convexToWorld);
}
void CollisionWorld::ClosestConvexResultCallback::ConvexToWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_convexToWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::HitNormalWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_hitNormalWorld);
}
void CollisionWorld::ClosestConvexResultCallback::HitNormalWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_hitNormalWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::HitPointWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_hitPointWorld);
}
void CollisionWorld::ClosestConvexResultCallback::HitPointWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_hitPointWorld);
}

btCollisionWorld::ClosestConvexResultCallback* CollisionWorld::ClosestConvexResultCallback::UnmanagedPointer::get()
{
	return (btCollisionWorld::ClosestConvexResultCallback*)ConvexResultCallback::UnmanagedPointer;
}


CollisionWorld::ContactResultCallback::ContactResultCallback(btCollisionWorld::ContactResultCallback* callback)
{
	_callback = callback;
}

CollisionWorld::ContactResultCallback::~ContactResultCallback()
{
	this->!ContactResultCallback();
}

CollisionWorld::ContactResultCallback::!ContactResultCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

btScalar CollisionWorld::ContactResultCallback::AddSingleResult(ManifoldPoint^ cp,
	CollisionObject^ colObj0, int partId0, int index0,
	CollisionObject^ colObj1, int partId1, int index1)
{
	return _callback->addSingleResult(*cp->UnmanagedPointer,
		colObj0->UnmanagedPointer, partId0, index0,
		colObj1->UnmanagedPointer, partId1, index1);
}

bool CollisionWorld::ContactResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _callback->needsCollision(proxy0->UnmanagedPointer);
}

CollisionFilterGroups CollisionWorld::ContactResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterGroup;
}
void CollisionWorld::ContactResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::ContactResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterMask;
}
void CollisionWorld::ContactResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterMask = (short int)value;
}

bool CollisionWorld::ContactResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btCollisionWorld::ContactResultCallback* CollisionWorld::ContactResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::ContactResultCallback::UnmanagedPointer::set(btCollisionWorld::ContactResultCallback* value)
{
	_callback = value;
}


CollisionWorld::LocalShapeInfo::LocalShapeInfo(btCollisionWorld::LocalShapeInfo* info)
{
	_info = info;
}

btCollisionWorld::LocalShapeInfo* CollisionWorld::LocalShapeInfo::UnmanagedPointer::get()
{
	return _info;
}
void CollisionWorld::LocalShapeInfo::UnmanagedPointer::set(btCollisionWorld::LocalShapeInfo* value)
{
	_info = value;
}


CollisionWorld::LocalRayResult::LocalRayResult(BulletSharp::CollisionObject^ collisionObject, CollisionWorld::LocalShapeInfo^ localShapeInfo,
	Vector3 hitNormalLocal, btScalar hitFraction)
{
	_result = new btCollisionWorld::LocalRayResult(collisionObject->UnmanagedPointer, localShapeInfo->UnmanagedPointer,
		*Math::Vector3ToBtVector3(hitNormalLocal), hitFraction);
}

BulletSharp::CollisionObject^ CollisionWorld::LocalRayResult::CollisionObject::get()
{
	return gcnew BulletSharp::CollisionObject(_result->m_collisionObject);
}
void CollisionWorld::LocalRayResult::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_result->m_collisionObject = value->UnmanagedPointer;
}

btScalar CollisionWorld::LocalRayResult::HitFraction::get()
{
	return _result->m_hitFraction;
}
void CollisionWorld::LocalRayResult::HitFraction::set(btScalar value)
{
	_result->m_hitFraction = value;
}

Vector3 CollisionWorld::LocalRayResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_result->m_hitNormalLocal);
}
void CollisionWorld::LocalRayResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_result->m_hitNormalLocal);
}

CollisionWorld::LocalShapeInfo^ CollisionWorld::LocalRayResult::LocalShapeInfo::get()
{
	return gcnew CollisionWorld::LocalShapeInfo(_result->m_localShapeInfo);
}
void CollisionWorld::LocalRayResult::LocalShapeInfo::set(CollisionWorld::LocalShapeInfo^ value)
{
	_result->m_localShapeInfo = value->UnmanagedPointer;
}

btCollisionWorld::LocalRayResult* CollisionWorld::LocalRayResult::UnmanagedPointer::get()
{
	return _result;
}
void CollisionWorld::LocalRayResult::UnmanagedPointer::set(btCollisionWorld::LocalRayResult* value)
{
	_result = value;
}


CollisionWorld::RayResultCallback::RayResultCallback(btCollisionWorld::RayResultCallback* callback)
{
	_callback = callback;
}

CollisionWorld::RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

CollisionWorld::RayResultCallback::!RayResultCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

btScalar CollisionWorld::RayResultCallback::AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace)
{
	return _callback->addSingleResult(*rayResult->UnmanagedPointer, normalInWorldSpace);
}

bool CollisionWorld::RayResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _callback->needsCollision(proxy0->UnmanagedPointer);
}

BulletSharp::CollisionObject^ CollisionWorld::RayResultCallback::CollisionObject::get()
{
	return gcnew BulletSharp::CollisionObject(_callback->m_collisionObject);
}
void CollisionWorld::RayResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_callback->m_collisionObject = value->UnmanagedPointer;
}

btScalar CollisionWorld::RayResultCallback::ClosestHitFraction::get()
{
	return _callback->m_closestHitFraction;
}
void CollisionWorld::RayResultCallback::ClosestHitFraction::set(btScalar value)
{
	_callback->m_closestHitFraction = value;
}

CollisionFilterGroups CollisionWorld::RayResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterGroup;
}
void CollisionWorld::RayResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::RayResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_callback->m_collisionFilterMask;
}
void CollisionWorld::RayResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_callback->m_collisionFilterMask = (short int)value;
}

unsigned int CollisionWorld::RayResultCallback::Flags::get()
{
	return _callback->m_flags;
}
void CollisionWorld::RayResultCallback::Flags::set(unsigned int value)
{
	_callback->m_flags = value;
}

bool CollisionWorld::RayResultCallback::HasHit::get()
{
	return _callback->hasHit();
}

bool CollisionWorld::RayResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btCollisionWorld::RayResultCallback* CollisionWorld::RayResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::RayResultCallback::UnmanagedPointer::set(btCollisionWorld::RayResultCallback* value)
{
	_callback = value;
}


CollisionWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld)
: RayResultCallback(new btCollisionWorld::ClosestRayResultCallback(
	*Math::Vector3ToBtVector3(rayFromWorld), *Math::Vector3ToBtVector3(rayToWorld)))
{
}

Vector3 CollisionWorld::ClosestRayResultCallback::HitNormalWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_hitNormalWorld);
}
void CollisionWorld::ClosestRayResultCallback::HitNormalWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_hitNormalWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::HitPointWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_hitPointWorld);
}
void CollisionWorld::ClosestRayResultCallback::HitPointWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_hitPointWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::RayFromWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_rayFromWorld);
}
void CollisionWorld::ClosestRayResultCallback::RayFromWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_rayFromWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::RayToWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_rayToWorld);
}
void CollisionWorld::ClosestRayResultCallback::RayToWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_rayToWorld);
}

btCollisionWorld::ClosestRayResultCallback* CollisionWorld::ClosestRayResultCallback::UnmanagedPointer::get()
{
	return (btCollisionWorld::ClosestRayResultCallback*)RayResultCallback::UnmanagedPointer;
}


CollisionWorld::CollisionWorld(btCollisionWorld* world)
{
	_world = world;
}

CollisionWorld::CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration)
{
	_world = new btCollisionWorld(dispatcher->UnmanagedPointer, pairCache->UnmanagedPointer, collisionConfiguration->UnmanagedPointer);
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

CollisionWorld::~CollisionWorld()
{
	this->!CollisionWorld();
}

CollisionWorld::!CollisionWorld()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_world = NULL;
	
	OnDisposed( this, nullptr );
}

bool CollisionWorld::IsDisposed::get()
{
	return (_world == NULL);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback)
{
	_world->contactPairTest(colObjA->UnmanagedPointer, colObjB->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

void CollisionWorld::ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback)
{
	_world->contactTest(colObj->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration)
{
	_world->convexSweepTest(castShape->UnmanagedPointer, *Math::MatrixToBtTransform(from), *Math::MatrixToBtTransform(to),
		*resultCallback->UnmanagedPointer, allowedCcdPenetration);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback)
{
	_world->convexSweepTest(castShape->UnmanagedPointer, *Math::MatrixToBtTransform(from), *Math::MatrixToBtTransform(to),
		*resultCallback->UnmanagedPointer);
}

#ifndef DISABLE_DEBUGDRAW
void CollisionWorld::DebugDrawObject(Matrix worldTransform, CollisionShape^ shape, BtColor color)
{
	_world->debugDrawObject(*Math::MatrixToBtTransform(worldTransform), shape->UnmanagedPointer, BtColorToBtVector(color));
}

void CollisionWorld::DebugDrawWorld()
{
	UnmanagedPointer->debugDrawWorld();
}
#endif

void CollisionWorld::ObjectQuerySingle(ConvexShape^ castShape, Matrix rayFromTrans, Matrix rayToTrans,
	CollisionObject^ collisionObject, CollisionShape^ collisionShape, Matrix colObjWorldTransform,
	ConvexResultCallback^ resultCallback, btScalar allowedPenetration)
{
	btCollisionWorld::objectQuerySingle(castShape->UnmanagedPointer, *Math::MatrixToBtTransform(rayFromTrans),
		*Math::MatrixToBtTransform(rayToTrans), collisionObject->UnmanagedPointer, collisionShape->UnmanagedPointer,
		*Math::MatrixToBtTransform(colObjWorldTransform), *resultCallback->UnmanagedPointer, allowedPenetration);
}

void CollisionWorld::PerformDiscreteCollisionDetection()
{
	_world->performDiscreteCollisionDetection();
}

void CollisionWorld::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback)
{
	_world->rayTest(*Math::Vector3ToBtVector3(rayFromWorld), *Math::Vector3ToBtVector3(rayToWorld),
		*resultCallback->UnmanagedPointer);
}

void CollisionWorld::RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans, CollisionObject^ collisionObject,
	CollisionShape^ collisionShape, Matrix colObjWorldTransform, RayResultCallback^ resultCallback)
{
	btCollisionWorld::rayTestSingle(*Math::MatrixToBtTransform(rayFromTrans), *Math::MatrixToBtTransform(rayToTrans),
		collisionObject->UnmanagedPointer, collisionShape->UnmanagedPointer,
		*Math::MatrixToBtTransform(colObjWorldTransform), *resultCallback->UnmanagedPointer);
}

void CollisionWorld::RemoveCollisionObject(CollisionObject^ collisionObject)
{
	_world->removeCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::UpdateAabbs()
{
	_world->updateAabbs();
}

void CollisionWorld::UpdateSingleAabb(CollisionObject^ colObj)
{
	_world->updateSingleAabb(colObj->UnmanagedPointer);
}

BroadphaseInterface^ CollisionWorld::Broadphase::get()
{
	return _broadphase;
}
void CollisionWorld::Broadphase::set(BroadphaseInterface^ value)
{
	_world->setBroadphase(value->UnmanagedPointer);
	_broadphase = value;
}

BulletSharp::CollisionObjectArray^ CollisionWorld::CollisionObjectArray::get()
{
	if (_collisionObjects == nullptr)
	{
		btCollisionObjectArray* objArray = new btCollisionObjectArray;
		*objArray = _world->getCollisionObjectArray();;
		_collisionObjects = gcnew BulletSharp::CollisionObjectArray(objArray);
	}
	return _collisionObjects;
}

#ifndef DISABLE_DEBUGDRAW
DebugDraw^ CollisionWorld::DebugDrawer::get()
{
	return _debugDraw;
}
void CollisionWorld::DebugDrawer::set(DebugDraw^ value)
{
	if (value == nullptr)
		_world->setDebugDrawer(0);
	else
		_world->setDebugDrawer(value->UnmanagedPointer);
}
#endif

BulletSharp::Dispatcher^ CollisionWorld::Dispatcher::get()
{
	return _dispatcher;
}

DispatcherInfo^ CollisionWorld::DispatchInfo::get()
{
	return gcnew DispatcherInfo(&_world->getDispatchInfo());;
}

bool CollisionWorld::ForceUpdateAllAabbs::get()
{
	return _world->getForceUpdateAllAabbs();
}
void CollisionWorld::ForceUpdateAllAabbs::set(bool value)
{
	_world->setForceUpdateAllAabbs(value);
}

int CollisionWorld::NumCollisionObjects::get()
{
	return _world->getNumCollisionObjects();
}

OverlappingPairCache^ CollisionWorld::PairCache::get()
{
	return _pairCache;
}

btCollisionWorld* CollisionWorld::UnmanagedPointer::get()
{
	return _world;
}
void CollisionWorld::UnmanagedPointer::set(btCollisionWorld* value)
{
	_world = value;
}
