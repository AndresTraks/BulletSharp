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
#include "IActionInterface.h"
#include "ManifoldPoint.h"
#include "OverlappingPairCache.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#include "IDebugDraw.h"
#endif
#ifndef DISABLE_VEHICLE
#include "RaycastVehicle.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftRigidDynamicsWorld.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "CharacterControllerInterface.h"
#endif

int CollisionWorld::LocalShapeInfo::ShapePart::get()
{
	return _native->m_shapePart;
}
void CollisionWorld::LocalShapeInfo::ShapePart::set(int value)
{
	_native->m_shapePart = value;
}

int CollisionWorld::LocalShapeInfo::TriangleIndex::get()
{
	return _native->m_triangleIndex;
}
void CollisionWorld::LocalShapeInfo::TriangleIndex::set(int value)
{
	_native->m_triangleIndex = value;
}


CollisionWorld::LocalConvexResult::LocalConvexResult(BulletSharp::CollisionObject^ collisionObject, CollisionWorld::LocalShapeInfo^ localShapeInfo,
	Vector3 hitNormalLocal, Vector3 hitPointLocal, btScalar hitFraction)
{
	VECTOR3_DEF(hitNormalLocal);
	VECTOR3_DEF(hitPointLocal);

	_native = new btCollisionWorld::LocalConvexResult(collisionObject->_native, localShapeInfo->_native,
		VECTOR3_USE(hitNormalLocal), VECTOR3_USE(hitPointLocal), hitFraction);

	VECTOR3_DEL(hitNormalLocal);
	VECTOR3_DEL(hitPointLocal);
}

CollisionObject^ CollisionWorld::LocalConvexResult::HitCollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_hitCollisionObject);
}
void CollisionWorld::LocalConvexResult::HitCollisionObject::set(CollisionObject^ value)
{
	_native->m_hitCollisionObject = value->_native;
}

btScalar CollisionWorld::LocalConvexResult::HitFraction::get()
{
	return _native->m_hitFraction;
}
void CollisionWorld::LocalConvexResult::HitFraction::set(btScalar value)
{
	_native->m_hitFraction = value;
}

Vector3 CollisionWorld::LocalConvexResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitNormalLocal);
}
void CollisionWorld::LocalConvexResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitNormalLocal);
}

Vector3 CollisionWorld::LocalConvexResult::HitPointLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitPointLocal);
}
void CollisionWorld::LocalConvexResult::HitPointLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitPointLocal);
}

CollisionWorld::LocalShapeInfo^ CollisionWorld::LocalConvexResult::LocalShapeInfo::get()
{
	return gcnew CollisionWorld::LocalShapeInfo(_native->m_localShapeInfo);
}
void CollisionWorld::LocalConvexResult::LocalShapeInfo::set(CollisionWorld::LocalShapeInfo^ value)
{
	_native->m_localShapeInfo = value->_native;
}


CollisionWorld::ConvexResultCallback::ConvexResultCallback(btCollisionWorld::ConvexResultCallback* native)
{
	_native = native;
}

CollisionWorld::ConvexResultCallback::~ConvexResultCallback()
{
	this->!ConvexResultCallback();
}

CollisionWorld::ConvexResultCallback::!ConvexResultCallback()
{
	if (this->IsDisposed)
		return;
	
	ALIGNED_FREE(_native);
	_native = NULL;
}

btScalar CollisionWorld::ConvexResultCallback::AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace)
{
	return _native->addSingleResult(*convexResult->_native, normalInWorldSpace);
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

	_native = ALIGNED_NEW(btCollisionWorld::ClosestConvexResultCallback) (VECTOR3_USE(convexFromWorld), VECTOR3_USE(convexToWorld));

	VECTOR3_DEL(convexFromWorld);
	VECTOR3_DEL(convexToWorld);
}

CollisionWorld::ClosestConvexResultCallback::ClosestConvexResultCallback(Vector3% convexFromWorld, Vector3% convexToWorld)
: ConvexResultCallback(0)
{
	VECTOR3_DEF(convexFromWorld);
	VECTOR3_DEF(convexToWorld);

	_native = ALIGNED_NEW(btCollisionWorld::ClosestConvexResultCallback) (VECTOR3_USE(convexFromWorld), VECTOR3_USE(convexToWorld));

	VECTOR3_DEL(convexFromWorld);
	VECTOR3_DEL(convexToWorld);
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

CollisionObject^ CollisionWorld::ClosestConvexResultCallback::HitCollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)Native->m_hitCollisionObject);
}
void CollisionWorld::ClosestConvexResultCallback::HitCollisionObject::set(CollisionObject^ value)
{
	Native->m_hitCollisionObject = value->_native;
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


CollisionWorld::ContactResultCallback::ContactResultCallback(ContactResultCallbackWrapper* native)
{
	_native = native;
}

CollisionWorld::ContactResultCallback::~ContactResultCallback()
{
	this->!ContactResultCallback();
}

CollisionWorld::ContactResultCallback::!ContactResultCallback()
{
	if (this->IsDisposed)
		return;
	
	delete _native;
	_native = NULL;
}

CollisionWorld::ContactResultCallback::ContactResultCallback()
{
	_native = new ContactResultCallbackWrapper(this);
}

bool CollisionWorld::ContactResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _native->baseNeedsCollision(proxy0->_native);
}

CollisionFilterGroups CollisionWorld::ContactResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterGroup;
}
void CollisionWorld::ContactResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups CollisionWorld::ContactResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterMask;
}
void CollisionWorld::ContactResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterMask = (short int)value;
}

bool CollisionWorld::ContactResultCallback::IsDisposed::get()
{
	return (_native == NULL);
}


CollisionWorld::LocalShapeInfo::LocalShapeInfo(btCollisionWorld::LocalShapeInfo* info)
{
	_native = info;
}


CollisionWorld::LocalRayResult::LocalRayResult(BulletSharp::CollisionObject^ collisionObject, CollisionWorld::LocalShapeInfo^ localShapeInfo,
	Vector3 hitNormalLocal, btScalar hitFraction)
{
	VECTOR3_DEF(hitNormalLocal);

	_native = new btCollisionWorld::LocalRayResult(collisionObject->_native, localShapeInfo->_native,
		VECTOR3_USE(hitNormalLocal), hitFraction);

	VECTOR3_DEL(hitNormalLocal);
}

BulletSharp::CollisionObject^ CollisionWorld::LocalRayResult::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void CollisionWorld::LocalRayResult::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = value->_native;
}

btScalar CollisionWorld::LocalRayResult::HitFraction::get()
{
	return _native->m_hitFraction;
}
void CollisionWorld::LocalRayResult::HitFraction::set(btScalar value)
{
	_native->m_hitFraction = value;
}

Vector3 CollisionWorld::LocalRayResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitNormalLocal);
}
void CollisionWorld::LocalRayResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitNormalLocal);
}

CollisionWorld::LocalShapeInfo^ CollisionWorld::LocalRayResult::LocalShapeInfo::get()
{
	return gcnew CollisionWorld::LocalShapeInfo(_native->m_localShapeInfo);
}
void CollisionWorld::LocalRayResult::LocalShapeInfo::set(CollisionWorld::LocalShapeInfo^ value)
{
	_native->m_localShapeInfo = value->_native;
}


CollisionWorld::RayResultCallback::RayResultCallback(btCollisionWorld::RayResultCallback* native)
{
	_native = native;
}

CollisionWorld::RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

CollisionWorld::RayResultCallback::!RayResultCallback()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

btScalar CollisionWorld::RayResultCallback::AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace)
{
	return _native->addSingleResult(*rayResult->_native, normalInWorldSpace);
}

bool CollisionWorld::RayResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	return _native->needsCollision(proxy0->_native);
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

CollisionObject^ CollisionWorld::RayResultCallback::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void CollisionWorld::RayResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = value->_native;
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

	_native = ALIGNED_NEW(btCollisionWorld::ClosestRayResultCallback) (VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld));

	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

CollisionWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3% rayFromWorld, Vector3% rayToWorld)
: RayResultCallback(0)
{
	VECTOR3_DEF(rayFromWorld);
	VECTOR3_DEF(rayToWorld);

	_native = ALIGNED_NEW(btCollisionWorld::ClosestRayResultCallback) (VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld));

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
	if (_collisionObjects == nullptr)
	{
		_collisionObjects = gcnew AlignedCollisionObjectArray((btAlignedObjectArray<btCollisionObject*>*)&Native->m_collisionObjects);
	}
	return _collisionObjects;
}

AlignedScalarArray^ CollisionWorld::AllHitsRayResultCallback::HitFractions::get()
{
	if (_hitFractions == nullptr)
	{
		_hitFractions = gcnew AlignedScalarArray(&Native->m_hitFractions);
	}
	return _hitFractions;
}

AlignedVector3Array^ CollisionWorld::AllHitsRayResultCallback::HitNormalWorld::get()
{
	if (_hitNormalWorld == nullptr)
	{
		_hitNormalWorld = gcnew AlignedVector3Array(&Native->m_hitNormalWorld);
	}
	return _hitNormalWorld;
}

AlignedVector3Array^ CollisionWorld::AllHitsRayResultCallback::HitPointWorld::get()
{
	if (_hitPointWorld == nullptr)
	{
		_hitPointWorld = gcnew AlignedVector3Array(&Native->m_hitPointWorld);
	}
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


CollisionWorld::CollisionWorld(btCollisionWorld* native)
{
	_native = native;
}

CollisionWorld::CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ broadphasePairCache,
	BulletSharp::CollisionConfiguration^ collisionConfiguration)
{
	_native = new btCollisionWorld(dispatcher->_native, broadphasePairCache->_native,
		collisionConfiguration->_native);
	_dispatcher = dispatcher;
	_broadphase = broadphasePairCache;
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
	
	btDynamicsWorld* dynamicsWorld = dynamic_cast<btDynamicsWorld*>(_native);
	if (dynamicsWorld != 0)
	{
		void* userObj = dynamicsWorld->getWorldUserInfo();
		if (userObj != 0)
		{
			VoidPtrToGCHandle(userObj).Free();
		}

		// Delete ActionInterfaceWrappers
		DynamicsWorld^ world = static_cast<DynamicsWorld^>(this);
		if (world->_actions)
		{
			for each (IActionInterface^ action in world->_actions)
			{
#ifndef DISABLE_VEHICLE
				RaycastVehicle^ vehicle = dynamic_cast<RaycastVehicle^>(action);
				if (vehicle) {
					continue;
				}
#endif
#ifndef DISABLE_UNCOMMON
				CharacterControllerInterface^ character = dynamic_cast<CharacterControllerInterface^>(action);
				if (character) {
					continue;
				}
#endif
				ActionInterfaceWrapper* wrapper = (ActionInterfaceWrapper*)ObjectTable::GetUnmanagedObject(action);
				ObjectTable::Remove(wrapper);
				delete wrapper;
			}
		}
	}

	if (_broadphase->IsDisposed) {
		//throw gcnew ObjectDisposedException("_broadphase",
		Console::WriteLine(
			"The BroadphaseInterface was disposed before the CollisionWorld. "
			"It is required for CollisionWorld cleanup, so dispose it later than the world.");
		return;
	}

	delete _native;
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask)
{
	_native->addCollisionObject(collisionObject->_native, (short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup)
{
	_native->addCollisionObject(collisionObject->_native, (short int)collisionFilterGroup);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject)
{
	_native->addCollisionObject(collisionObject->_native);
}

void CollisionWorld::ComputeOverlappingPairs()
{
	_native->computeOverlappingPairs();
}

void CollisionWorld::ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB,
	ContactResultCallback^ resultCallback)
{
	_native->contactPairTest(colObjA->_native, colObjB->_native, *resultCallback->_native);
}

void CollisionWorld::ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback)
{
	_native->contactTest(colObj->_native, *resultCallback->_native);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to,
	ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration)
{
	TRANSFORM_CONV(from);
	TRANSFORM_CONV(to);
	_native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(from), TRANSFORM_USE(to),
		*resultCallback->_native, allowedCcdPenetration);
	TRANSFORM_DEL(from);
	TRANSFORM_DEL(to);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to,
	ConvexResultCallback^ resultCallback)
{
	TRANSFORM_CONV(from);
	TRANSFORM_CONV(to);
	_native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(from), TRANSFORM_USE(to),
		*resultCallback->_native);
	TRANSFORM_DEL(from);
	TRANSFORM_DEL(to);
}

#ifndef DISABLE_DEBUGDRAW
void CollisionWorld::DebugDrawObject(Matrix worldTransform, CollisionShape^ shape, BtColor color)
{
	TRANSFORM_CONV(worldTransform);
	btVector3* colorTemp = BtColorToBtVector(color);
	_native->debugDrawObject(TRANSFORM_USE(worldTransform), shape->_native, *colorTemp);
	TRANSFORM_DEL(worldTransform);
	delete colorTemp;
}

void CollisionWorld::DebugDrawWorld()
{
	_native->debugDrawWorld();
}
#endif

void CollisionWorld::ObjectQuerySingle(ConvexShape^ castShape, Matrix rayFromTrans,
	Matrix rayToTrans, CollisionObject^ collisionObject, CollisionShape^ collisionShape,
	Matrix colObjWorldTransform, ConvexResultCallback^ resultCallback, btScalar allowedPenetration)
{
	TRANSFORM_CONV(rayFromTrans);
	TRANSFORM_CONV(rayToTrans);
	TRANSFORM_CONV(colObjWorldTransform);
	btCollisionWorld::objectQuerySingle((btConvexShape*)castShape->_native, TRANSFORM_USE(rayFromTrans),
		TRANSFORM_USE(rayToTrans), collisionObject->_native, collisionShape->_native,
		TRANSFORM_USE(colObjWorldTransform), *resultCallback->_native, allowedPenetration);
	TRANSFORM_DEL(rayFromTrans);
	TRANSFORM_DEL(rayToTrans);
	TRANSFORM_DEL(colObjWorldTransform);
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
	TRANSFORM_CONV(rayFromTrans);
	TRANSFORM_CONV(rayToTrans);
	TRANSFORM_CONV(colObjWorldTransform);
	btCollisionWorld::rayTestSingle(TRANSFORM_USE(rayFromTrans), TRANSFORM_USE(rayToTrans),
		collisionObject->_native, collisionShape->_native, TRANSFORM_USE(colObjWorldTransform),
		*resultCallback->_native);
	TRANSFORM_DEL(rayFromTrans);
	TRANSFORM_DEL(rayToTrans);
	TRANSFORM_DEL(colObjWorldTransform);
}

void CollisionWorld::RemoveCollisionObject(CollisionObject^ collisionObject)
{
	_native->removeCollisionObject(collisionObject->_native);
}

#ifndef DISABLE_SERIALIZE
void CollisionWorld::Serialize(BulletSharp::Serializer^ serializer)
{
	_native->serialize(serializer->_native);
}
#endif

void CollisionWorld::UpdateAabbs()
{
	_native->updateAabbs();
}

void CollisionWorld::UpdateSingleAabb(CollisionObject^ colObj)
{
	_native->updateSingleAabb(colObj->_native);
}

BroadphaseInterface^ CollisionWorld::Broadphase::get()
{
	return _broadphase;
}
void CollisionWorld::Broadphase::set(BroadphaseInterface^ pairCache)
{
	_native->setBroadphase(pairCache->_native);
	_broadphase = pairCache;
}

AlignedCollisionObjectArray^ CollisionWorld::CollisionObjectArray::get()
{
	if (_collisionObjectArray == nullptr)
	{
		_collisionObjectArray = gcnew AlignedCollisionObjectArray(&_native->getCollisionObjectArray());
	}
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
void CollisionWorld::ForceUpdateAllAabbs::set(bool forceUpdateAllAabbs)
{
	_native->setForceUpdateAllAabbs(forceUpdateAllAabbs);
}

bool CollisionWorld::IsDisposed::get()
{
	return (_native == NULL);
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
