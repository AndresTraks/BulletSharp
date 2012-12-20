#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"
#include "CollisionWorld.h"
#include "ConvexShape.h"
#include "DynamicsWorld.h"
#include "Dispatcher.h"
#include "ManifoldPoint.h"
#include "OverlappingPairCache.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#include "IDebugDraw.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftRigidDynamicsWorld.h"
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
	VECTOR3_DEF(hitNormalLocal);
	VECTOR3_DEF(hitPointLocal);

	_result = new btCollisionWorld::LocalConvexResult(collisionObject->UnmanagedPointer, localShapeInfo->UnmanagedPointer,
		VECTOR3_USE(hitNormalLocal), VECTOR3_USE(hitPointLocal), hitFraction);

	VECTOR3_DEL(hitNormalLocal);
	VECTOR3_DEL(hitPointLocal);
}

BulletSharp::CollisionObject^ CollisionWorld::LocalConvexResult::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_result->m_hitCollisionObject);
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
	_native = callback;
}

CollisionWorld::ConvexResultCallback::~ConvexResultCallback()
{
	this->!ConvexResultCallback();
}

CollisionWorld::ConvexResultCallback::!ConvexResultCallback()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	delete _native;
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

btScalar CollisionWorld::ConvexResultCallback::AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace)
{
	return _native->addSingleResult(*convexResult->UnmanagedPointer, normalInWorldSpace);
}

bool CollisionWorld::ConvexResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _native->needsCollision(proxy0->_native);
}

btScalar CollisionWorld::ConvexResultCallback::ClosestHitFraction::get()
{
	return _native->m_closestHitFraction;
}
void CollisionWorld::ConvexResultCallback::ClosestHitFraction::set(btScalar value)
{
	_native->m_closestHitFraction = value;
}

CollisionFilterGroups CollisionWorld::ConvexResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterGroup;
}
void CollisionWorld::ConvexResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::ConvexResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterMask;
}
void CollisionWorld::ConvexResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterMask = (short int)value;
}

bool CollisionWorld::ConvexResultCallback::HasHit::get()
{
	return _native->hasHit();
}

bool CollisionWorld::ConvexResultCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#define Native static_cast<btCollisionWorld::ClosestConvexResultCallback*>(_native)

CollisionWorld::ClosestConvexResultCallback::ClosestConvexResultCallback(Vector3 convexFromWorld, Vector3 convexToWorld)
: ConvexResultCallback(0)
{
	VECTOR3_DEF(convexFromWorld);
	VECTOR3_DEF(convexToWorld);

	_native = new btCollisionWorld::ClosestConvexResultCallback(VECTOR3_USE(convexFromWorld), VECTOR3_USE(convexToWorld));

	VECTOR3_DEL(convexFromWorld);
	VECTOR3_DEL(convexToWorld);
}

CollisionWorld::ClosestConvexResultCallback::ClosestConvexResultCallback(Vector3% convexFromWorld, Vector3% convexToWorld)
: ConvexResultCallback(0)
{
	VECTOR3_DEF(convexFromWorld);
	VECTOR3_DEF(convexToWorld);

	_native = new btCollisionWorld::ClosestConvexResultCallback(VECTOR3_USE(convexFromWorld), VECTOR3_USE(convexToWorld));

	VECTOR3_DEL(convexFromWorld);
	VECTOR3_DEL(convexToWorld);
}

BulletSharp::CollisionObject^ CollisionWorld::ClosestConvexResultCallback::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)Native->m_hitCollisionObject);
}
void CollisionWorld::ClosestConvexResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	Native->m_hitCollisionObject = value->_native;
}

Vector3 CollisionWorld::ClosestConvexResultCallback::ConvexFromWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_convexFromWorld);
}
void CollisionWorld::ClosestConvexResultCallback::ConvexFromWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_convexFromWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::ConvexToWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_convexToWorld);
}
void CollisionWorld::ClosestConvexResultCallback::ConvexToWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_convexToWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::HitNormalWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_hitNormalWorld);
}
void CollisionWorld::ClosestConvexResultCallback::HitNormalWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_hitNormalWorld);
}

Vector3 CollisionWorld::ClosestConvexResultCallback::HitPointWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_hitPointWorld);
}
void CollisionWorld::ClosestConvexResultCallback::HitPointWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_hitPointWorld);
}


CollisionWorld::ContactResultCallback::ContactResultCallback(ContactResultCallbackWrapper* callback)
{
	_callback = callback;
}

CollisionWorld::ContactResultCallback::~ContactResultCallback()
{
	this->!ContactResultCallback();
}

CollisionWorld::ContactResultCallback::!ContactResultCallback()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	_callback = NULL;
	
	OnDisposed(this, nullptr);
}

CollisionWorld::ContactResultCallback::ContactResultCallback()
{
	_callback = new ContactResultCallbackWrapper(this);
}

bool CollisionWorld::ContactResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _callback->baseNeedsCollision(proxy0->_native);
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

ContactResultCallbackWrapper* CollisionWorld::ContactResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::ContactResultCallback::UnmanagedPointer::set(ContactResultCallbackWrapper* value)
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
	VECTOR3_DEF(hitNormalLocal);

	_result = new btCollisionWorld::LocalRayResult(collisionObject->UnmanagedPointer, localShapeInfo->UnmanagedPointer,
		VECTOR3_USE(hitNormalLocal), hitFraction);

	VECTOR3_DEL(hitNormalLocal);
}

BulletSharp::CollisionObject^ CollisionWorld::LocalRayResult::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_result->m_collisionObject);
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
	_native = callback;
}

CollisionWorld::RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

CollisionWorld::RayResultCallback::!RayResultCallback()
{
	delete _native;
	_native = NULL;
}

btScalar CollisionWorld::RayResultCallback::AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace)
{
	return _native->addSingleResult(*rayResult->UnmanagedPointer, normalInWorldSpace);
}

bool CollisionWorld::RayResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _native->needsCollision(proxy0->_native);
}

BulletSharp::CollisionObject^ CollisionWorld::RayResultCallback::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void CollisionWorld::RayResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = value->UnmanagedPointer;
}

btScalar CollisionWorld::RayResultCallback::ClosestHitFraction::get()
{
	return _native->m_closestHitFraction;
}
void CollisionWorld::RayResultCallback::ClosestHitFraction::set(btScalar value)
{
	_native->m_closestHitFraction = value;
}

CollisionFilterGroups CollisionWorld::RayResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterGroup;
}
void CollisionWorld::RayResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::RayResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterMask;
}
void CollisionWorld::RayResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterMask = (short int)value;
}

unsigned int CollisionWorld::RayResultCallback::Flags::get()
{
	return _native->m_flags;
}
void CollisionWorld::RayResultCallback::Flags::set(unsigned int value)
{
	_native->m_flags = value;
}

bool CollisionWorld::RayResultCallback::HasHit::get()
{
	return _native->hasHit();
}

bool CollisionWorld::RayResultCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#undef Native
#define Native static_cast<btCollisionWorld::ClosestRayResultCallback*>(_native)

CollisionWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld)
: RayResultCallback(0)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native = new btCollisionWorld::ClosestRayResultCallback(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld));

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

CollisionWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3% rayFromWorld, Vector3% rayToWorld)
: RayResultCallback(0)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native = new btCollisionWorld::ClosestRayResultCallback(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld));

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::HitNormalWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_hitNormalWorld);
}
void CollisionWorld::ClosestRayResultCallback::HitNormalWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_hitNormalWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::HitPointWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_hitPointWorld);
}
void CollisionWorld::ClosestRayResultCallback::HitPointWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_hitPointWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::RayFromWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayFromWorld);
}
void CollisionWorld::ClosestRayResultCallback::RayFromWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayFromWorld);
}

Vector3 CollisionWorld::ClosestRayResultCallback::RayToWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayToWorld);
}
void CollisionWorld::ClosestRayResultCallback::RayToWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayToWorld);
}


#undef Native
#define Native static_cast<btCollisionWorld::AllHitsRayResultCallback*>(_native)

CollisionWorld::AllHitsRayResultCallback::AllHitsRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld)
: RayResultCallback(0)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native = new btCollisionWorld::AllHitsRayResultCallback(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld));

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

AlignedCollisionObjectArray^ CollisionWorld::AllHitsRayResultCallback::CollisionObjects::get()
{
	btAlignedObjectArray<const btCollisionObject*>* collisionObjects = &Native->m_collisionObjects;
	if (_collisionObjects != nullptr && _collisionObjects->_native == collisionObjects)
		return _collisionObjects;

	_collisionObjects = gcnew AlignedCollisionObjectArray((btAlignedObjectArray<btCollisionObject*>*)collisionObjects);
	return _collisionObjects;
}

AlignedScalarArray^ CollisionWorld::AllHitsRayResultCallback::HitFractions::get()
{
	btAlignedObjectArray<btScalar>* hitFractions = &Native->m_hitFractions;
	if (_hitFractions != nullptr && _hitFractions->_native == hitFractions)
		return _hitFractions;

	_hitFractions = gcnew AlignedScalarArray(hitFractions);
	return _hitFractions;
}

AlignedVector3Array^ CollisionWorld::AllHitsRayResultCallback::HitNormalWorld::get()
{
	btAlignedObjectArray<btVector3>* hitNormalWorld = &Native->m_hitNormalWorld;
	if (_hitNormalWorld != nullptr && _hitNormalWorld->_native == hitNormalWorld)
		return _hitNormalWorld;

	_hitNormalWorld = gcnew AlignedVector3Array(hitNormalWorld);
	return _hitNormalWorld;
}

AlignedVector3Array^ CollisionWorld::AllHitsRayResultCallback::HitPointWorld::get()
{
	btAlignedObjectArray<btVector3>* hitPointWorld = &Native->m_hitPointWorld;
	if (_hitPointWorld != nullptr && _hitPointWorld->_native == hitPointWorld)
		return _hitNormalWorld;

	_hitPointWorld = gcnew AlignedVector3Array(hitPointWorld);
	return _hitPointWorld;
}

Vector3 CollisionWorld::AllHitsRayResultCallback::RayFromWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayFromWorld);
}
void CollisionWorld::AllHitsRayResultCallback::RayFromWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayFromWorld);
}

Vector3 CollisionWorld::AllHitsRayResultCallback::RayToWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayToWorld);
}
void CollisionWorld::AllHitsRayResultCallback::RayToWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayToWorld);
}


CollisionWorld::CollisionWorld(btCollisionWorld* world)
{
	_native = world;
}

CollisionWorld::CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration)
{
	_native = new btCollisionWorld(dispatcher->_native, pairCache->_native, collisionConfiguration->_native);
	_collisionConfiguration = collisionConfiguration;
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

CollisionWorld::~CollisionWorld()
{
	this->!CollisionWorld();
}

CollisionWorld::!CollisionWorld()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	btDynamicsWorld* dynamicsWorld = static_cast<btDynamicsWorld*>(_native);
	if (dynamicsWorld != 0)
	{
		void* userObj = dynamicsWorld->getWorldUserInfo();
		if (userObj != 0)
		{
			VoidPtrToGCHandle(userObj).Free();
		}
	}

	delete _native;
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

bool CollisionWorld::IsDisposed::get()
{
	return (_native == NULL);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	_native->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup)
{
	_native->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject)
{
	_native->addCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::ComputeOverlappingPairs()
{
	_native->computeOverlappingPairs();
}

void CollisionWorld::ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback)
{
	_native->contactPairTest(colObjA->UnmanagedPointer, colObjB->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

void CollisionWorld::ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback)
{
	_native->contactTest(colObj->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration)
{
	btTransform* fromTemp = Math::MatrixToBtTransform(from);
	btTransform* toTemp = Math::MatrixToBtTransform(to);

	_native->convexSweepTest((btConvexShape*)castShape->_native, *fromTemp, *toTemp, *resultCallback->_native, allowedCcdPenetration);

	ALIGNED_DEL(toTemp);
	ALIGNED_DEL(fromTemp);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to, ConvexResultCallback^ resultCallback)
{
	btTransform* fromTemp = Math::MatrixToBtTransform(from);
	btTransform* toTemp = Math::MatrixToBtTransform(to);

	_native->convexSweepTest((btConvexShape*)castShape->_native, *fromTemp, *toTemp, *resultCallback->_native);

	ALIGNED_DEL(toTemp);
	ALIGNED_DEL(fromTemp);
}

#ifndef DISABLE_DEBUGDRAW
void CollisionWorld::DebugDrawObject(Matrix worldTransform, CollisionShape^ shape, BtColor color)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	btVector3* colorTemp = BtColorToBtVector(color);
	
	_native->debugDrawObject(*worldTransformTemp, shape->_native, *colorTemp);
	
	ALIGNED_DEL(worldTransformTemp);
	delete colorTemp;
}

void CollisionWorld::DebugDrawWorld()
{
	_native->debugDrawWorld();
}
#endif

void CollisionWorld::ObjectQuerySingle(ConvexShape^ castShape, Matrix rayFromTrans, Matrix rayToTrans,
	CollisionObject^ collisionObject, CollisionShape^ collisionShape, Matrix colObjWorldTransform,
	ConvexResultCallback^ resultCallback, btScalar allowedPenetration)
{
	btTransform* rayFromTransTemp = Math::MatrixToBtTransform(rayFromTrans);
	btTransform* rayToTransTemp = Math::MatrixToBtTransform(rayToTrans);
	btTransform* colObjWorldTransformTemp = Math::MatrixToBtTransform(colObjWorldTransform);

	btCollisionWorld::objectQuerySingle((btConvexShape*)castShape->_native, *rayFromTransTemp, *rayToTransTemp,
		collisionObject->_native, collisionShape->_native,
		*colObjWorldTransformTemp, *resultCallback->_native, allowedPenetration);

	ALIGNED_DEL(colObjWorldTransformTemp);
	ALIGNED_DEL(rayToTransTemp);
	ALIGNED_DEL(rayFromTransTemp);
}

void CollisionWorld::PerformDiscreteCollisionDetection()
{
	_native->performDiscreteCollisionDetection();
}

void CollisionWorld::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_native);

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

void CollisionWorld::RayTest(Vector3% rayFromWorld, Vector3% rayToWorld, RayResultCallback^ resultCallback)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_native);

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

void CollisionWorld::RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans, CollisionObject^ collisionObject,
	CollisionShape^ collisionShape, Matrix colObjWorldTransform, RayResultCallback^ resultCallback)
{
	btTransform* rayFromTransTemp = Math::MatrixToBtTransform(rayFromTrans);
	btTransform* rayToTransTemp = Math::MatrixToBtTransform(rayToTrans);
	btTransform* colObjWorldTransformTemp = Math::MatrixToBtTransform(colObjWorldTransform);

	btCollisionWorld::rayTestSingle(*rayFromTransTemp, *rayToTransTemp,
		collisionObject->_native, collisionShape->_native,
		*colObjWorldTransformTemp, *resultCallback->_native);

	ALIGNED_DEL(rayFromTransTemp);
	ALIGNED_DEL(rayToTransTemp);
	ALIGNED_DEL(colObjWorldTransformTemp);
}

void CollisionWorld::RemoveCollisionObject(CollisionObject^ collisionObject)
{
	_native->removeCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::UpdateAabbs()
{
	_native->updateAabbs();
}

void CollisionWorld::UpdateSingleAabb(CollisionObject^ colObj)
{
	_native->updateSingleAabb(colObj->UnmanagedPointer);
}

#ifndef DISABLE_SERIALIZE
void CollisionWorld::Serialize(BulletSharp::Serializer^ serializer)
{
	_native->serialize(serializer->UnmanagedPointer);
}
#endif

BroadphaseInterface^ CollisionWorld::Broadphase::get()
{
	return _broadphase;
}
void CollisionWorld::Broadphase::set(BroadphaseInterface^ value)
{
	_native->setBroadphase(value->_native);
	_broadphase = value;
}

AlignedCollisionObjectArray^ CollisionWorld::CollisionObjectArray::get()
{
	btCollisionObjectArray* collisionObjectArray = &_native->getCollisionObjectArray();
	if (_collisionObjectArray != nullptr && _collisionObjectArray->_native == collisionObjectArray)
		return _collisionObjectArray;

	_collisionObjectArray = gcnew AlignedCollisionObjectArray(collisionObjectArray);
	return _collisionObjectArray;
}

#ifndef DISABLE_DEBUGDRAW
IDebugDraw^ CollisionWorld::DebugDrawer::get()
{
	return DebugDraw::GetManaged(_native->getDebugDrawer());
}
void CollisionWorld::DebugDrawer::set(IDebugDraw^ value)
{
	_native->setDebugDrawer(DebugDraw::GetUnmanaged(value));
}
#endif

BulletSharp::Dispatcher^ CollisionWorld::Dispatcher::get()
{
	return _dispatcher;
}

DispatcherInfo^ CollisionWorld::DispatchInfo::get()
{
	return gcnew DispatcherInfo(&_native->getDispatchInfo());
}

bool CollisionWorld::ForceUpdateAllAabbs::get()
{
	return _native->getForceUpdateAllAabbs();
}
void CollisionWorld::ForceUpdateAllAabbs::set(bool value)
{
	_native->setForceUpdateAllAabbs(value);
}

int CollisionWorld::NumCollisionObjects::get()
{
	return _native->getNumCollisionObjects();
}

OverlappingPairCache^ CollisionWorld::PairCache::get()
{
	return dynamic_cast<OverlappingPairCache^>(OverlappingPairCache::GetManaged(_native->getPairCache()));
}


ContactResultCallbackWrapper::ContactResultCallbackWrapper(CollisionWorld::ContactResultCallback^ callback)
{
	_callback = callback;
}

bool ContactResultCallbackWrapper::needsCollision(btBroadphaseProxy* proxy0) const
{
	return _callback->NeedsCollision(BroadphaseProxy::GetManaged(proxy0));
}

btScalar ContactResultCallbackWrapper::addSingleResult(btManifoldPoint& cp,
	const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
	const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	return _callback->AddSingleResult(gcnew ManifoldPoint(&cp),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);
}

bool ContactResultCallbackWrapper::baseNeedsCollision(btBroadphaseProxy* proxy0) const
{
	return btCollisionWorld::ContactResultCallback::needsCollision(proxy0);
}
