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
#include "Dispatcher.h"
#include "DynamicsWorld.h"
#include "IAction.h"
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
#ifndef DISABLE_UNCOMMON
#include "ICharacterController.h"
#endif

LocalShapeInfo::LocalShapeInfo(btCollisionWorld::LocalShapeInfo* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

LocalShapeInfo::~LocalShapeInfo()
{
	this->!LocalShapeInfo();
}

LocalShapeInfo::!LocalShapeInfo()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

LocalShapeInfo::LocalShapeInfo()
{
	_native = new btCollisionWorld::LocalShapeInfo();
}

int LocalShapeInfo::ShapePart::get()
{
	return _native->m_shapePart;
}
void LocalShapeInfo::ShapePart::set(int value)
{
	_native->m_shapePart = value;
}

int LocalShapeInfo::TriangleIndex::get()
{
	return _native->m_triangleIndex;
}
void LocalShapeInfo::TriangleIndex::set(int value)
{
	_native->m_triangleIndex = value;
}


LocalRayResult::LocalRayResult(btCollisionWorld::LocalRayResult* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

LocalRayResult::~LocalRayResult()
{
	this->!LocalRayResult();
}

LocalRayResult::!LocalRayResult()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

LocalRayResult::LocalRayResult(BulletSharp::CollisionObject^ collisionObject, BulletSharp::LocalShapeInfo^ localShapeInfo,
	Vector3 hitNormalLocal, btScalar hitFraction)
{
	VECTOR3_CONV(hitNormalLocal);
	_native = new btCollisionWorld::LocalRayResult(collisionObject->_native, localShapeInfo->_native,
		VECTOR3_USE(hitNormalLocal), hitFraction);
	VECTOR3_DEL(hitNormalLocal);

	_localShapeInfo = localShapeInfo;
}

CollisionObject^ LocalRayResult::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void LocalRayResult::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = GetUnmanagedNullable(value);
}

btScalar LocalRayResult::HitFraction::get()
{
	return _native->m_hitFraction;
}
void LocalRayResult::HitFraction::set(btScalar value)
{
	_native->m_hitFraction = value;
}

Vector3 LocalRayResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitNormalLocal);
}
void LocalRayResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitNormalLocal);
}

BulletSharp::LocalShapeInfo^ LocalRayResult::LocalShapeInfo::get()
{
	if (_localShapeInfo && _localShapeInfo->_native == _native->m_localShapeInfo)
	{
		return _localShapeInfo;
	}
	if (!_native->m_localShapeInfo)
	{
		return nullptr;
	}
	_localShapeInfo = gcnew BulletSharp::LocalShapeInfo(_native->m_localShapeInfo, true);
	return _localShapeInfo;
}
void LocalRayResult::LocalShapeInfo::set(BulletSharp::LocalShapeInfo^ value)
{
	_localShapeInfo = value;
	_native->m_localShapeInfo = GetUnmanagedNullable(value);
}


float RayResultCallback::AddSingleResultUnmanaged(IntPtr rayResult, bool normalInWorldSpace)
{
	return AddSingleResult(gcnew LocalRayResult(static_cast<btCollisionWorld::LocalRayResult*>(rayResult.ToPointer()), true), normalInWorldSpace);
}

bool RayResultCallback::NeedsCollisionUnmanaged(IntPtr proxy0)
{
	return NeedsCollision(BroadphaseProxy::GetManaged(static_cast<btBroadphaseProxy*>(proxy0.ToPointer())));
}

RayResultCallback::RayResultCallback()
{
	_addSingleResult = gcnew AddSingleResultUnmanagedDelegate(this, &RayResultCallback::AddSingleResultUnmanaged);
	_needsCollision = gcnew NeedsCollisionUnmanagedDelegate(this, &RayResultCallback::NeedsCollisionUnmanaged);
	_native = ALIGNED_NEW(RayResultCallbackWrapper) (
		(pRayResultCallback_AddSingleResult) Marshal::GetFunctionPointerForDelegate(_addSingleResult).ToPointer(),
		(pRayResultCallback_NeedsCollision) Marshal::GetFunctionPointerForDelegate(_needsCollision).ToPointer());
}

RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

RayResultCallback::!RayResultCallback()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

bool RayResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	bool collides = (proxy0->CollisionFilterGroup & CollisionFilterMask) != CollisionFilterGroups::None;
	collides = collides && (CollisionFilterGroup & proxy0->CollisionFilterMask) != CollisionFilterGroups::None;
	return collides;
}

btScalar RayResultCallback::ClosestHitFraction::get()
{
	return _native->m_closestHitFraction;
}
void RayResultCallback::ClosestHitFraction::set(btScalar value)
{
	_native->m_closestHitFraction = value;
}

CollisionFilterGroups RayResultCallback::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterGroup;
}
void RayResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups RayResultCallback::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterMask;
}
void RayResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterMask = (short int)value;
}

CollisionObject^ RayResultCallback::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_collisionObject);
}
void RayResultCallback::CollisionObject::set(BulletSharp::CollisionObject^ value)
{
	_native->m_collisionObject = GetUnmanagedNullable(value);
}

unsigned int RayResultCallback::Flags::get()
{
	return _native->m_flags;
}
void RayResultCallback::Flags::set(unsigned int value)
{
	_native->m_flags = value;
}

bool RayResultCallback::HasHit::get()
{
	return _native->hasHit();
}

bool RayResultCallback::IsDisposed::get()
{
	return (_native == NULL);
}


#define Callback static_cast<BulletSharp::RayResultCallback^>(VoidPtrToGCHandle(_callback).Target)

RayResultCallbackWrapper::RayResultCallbackWrapper(pRayResultCallback_AddSingleResult addSingleResultCallback,
	pRayResultCallback_NeedsCollision needsCollisionCallback)
{
	_addSingleResultCallback = addSingleResultCallback;
	_needsCollisionCallback = needsCollisionCallback;
}

bool RayResultCallbackWrapper::needsCollision(btBroadphaseProxy* proxy0) const
{
	return _needsCollisionCallback(proxy0);
}

btScalar RayResultCallbackWrapper::addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
{
	return _addSingleResultCallback(rayResult, normalInWorldSpace);
}


AllHitsRayResultCallback::AllHitsRayResultCallback(Vector3 rayFromWorld,
	Vector3 rayToWorld)
{
	RayFromWorld = rayFromWorld;
	RayToWorld = rayToWorld;

	_collisionObjects = gcnew List<BulletSharp::CollisionObject^>();
	_hitFractions = gcnew List<btScalar>();
	_hitNormalWorld = gcnew List<Vector3>();
	_hitPointWorld = gcnew List<Vector3>();
}

#pragma managed(push, off)
void RayResultCallback_AddSingleResult(btCollisionWorld::LocalRayResult* rayResult, bool normalInWorldSpace,
	const btVector3* rayFromWorld, const btVector3* rayToWorld,
	btVector3* hitNormalWorld, btVector3* hitPointWorld)
{
	if (normalInWorldSpace)
	{
		*hitNormalWorld = rayResult->m_hitNormalLocal;
	}
	else
	{
		// need to transform normal into worldspace
		*hitNormalWorld = rayResult->m_collisionObject->getWorldTransform().getBasis()*rayResult->m_hitNormalLocal;
	}
	hitPointWorld->setInterpolate3(*rayFromWorld, *rayToWorld, rayResult->m_hitFraction);
}
#pragma managed(pop)
btScalar AllHitsRayResultCallback::AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace)
{
	CollisionObject = rayResult->CollisionObject;
	CollisionObjects->Add(CollisionObject);
	btVector3* hitNormalWorldTemp = ALIGNED_NEW(btVector3);
	btVector3* hitPointWorldTemp = ALIGNED_NEW(btVector3);
	btVector3* rayFromWorld = Math::Vector3ToBtVector3(RayFromWorld);
	btVector3* rayToWorld = Math::Vector3ToBtVector3(RayToWorld);
	RayResultCallback_AddSingleResult(rayResult->_native, normalInWorldSpace,
		rayFromWorld, rayToWorld, hitNormalWorldTemp, hitPointWorldTemp);
	HitNormalWorld->Add(Math::BtVector3ToVector3(hitNormalWorldTemp));
	HitPointWorld->Add(Math::BtVector3ToVector3(hitPointWorldTemp));
	ALIGNED_FREE(hitNormalWorldTemp);
	ALIGNED_FREE(hitPointWorldTemp);
	ALIGNED_FREE(rayFromWorld);
	ALIGNED_FREE(rayToWorld);
	HitFractions->Add(rayResult->HitFraction);
	return ClosestHitFraction;
}

IList<CollisionObject^>^ AllHitsRayResultCallback::CollisionObjects::get()
{
	return _collisionObjects;
}

IList<btScalar>^ AllHitsRayResultCallback::HitFractions::get()
{
	return _hitFractions;
}

IList<Vector3>^ AllHitsRayResultCallback::HitNormalWorld::get()
{
	return _hitNormalWorld;
}

IList<Vector3>^ AllHitsRayResultCallback::HitPointWorld::get()
{
	return _hitPointWorld;
}

Vector3 AllHitsRayResultCallback::RayFromWorld::get()
{
	return _rayFromWorld;
}
void AllHitsRayResultCallback::RayFromWorld::set(Vector3 value)
{
	_rayFromWorld = value;
}

Vector3 AllHitsRayResultCallback::RayToWorld::get()
{
	return _rayToWorld;
}
void AllHitsRayResultCallback::RayToWorld::set(Vector3 value)
{
	_rayToWorld = value;
}


LocalConvexResult::LocalConvexResult(btCollisionWorld::LocalConvexResult* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

LocalConvexResult::~LocalConvexResult()
{
	this->!LocalConvexResult();
}

LocalConvexResult::!LocalConvexResult()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

LocalConvexResult::LocalConvexResult(BulletSharp::CollisionObject^ hitCollisionObject,
	BulletSharp::LocalShapeInfo^ localShapeInfo, Vector3 hitNormalLocal, Vector3 hitPointLocal,
	btScalar hitFraction)
{
	VECTOR3_CONV(hitNormalLocal);
	VECTOR3_CONV(hitPointLocal);
	_native = new btCollisionWorld::LocalConvexResult(hitCollisionObject->_native,
		localShapeInfo->_native, VECTOR3_USE(hitNormalLocal), VECTOR3_USE(hitPointLocal),
		hitFraction);
	VECTOR3_DEL(hitNormalLocal);
	VECTOR3_DEL(hitPointLocal);

	_localShapeInfo = localShapeInfo;
}

CollisionObject^ LocalConvexResult::HitCollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->m_hitCollisionObject);
}
void LocalConvexResult::HitCollisionObject::set(CollisionObject^ value)
{
	_native->m_hitCollisionObject = GetUnmanagedNullable(value);
}

btScalar LocalConvexResult::HitFraction::get()
{
	return _native->m_hitFraction;
}
void LocalConvexResult::HitFraction::set(btScalar value)
{
	_native->m_hitFraction = value;
}

Vector3 LocalConvexResult::HitNormalLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitNormalLocal);
}
void LocalConvexResult::HitNormalLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitNormalLocal);
}

Vector3 LocalConvexResult::HitPointLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_hitPointLocal);
}
void LocalConvexResult::HitPointLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_hitPointLocal);
}

LocalShapeInfo^ LocalConvexResult::LocalShapeInfo::get()
{
	return _localShapeInfo;
}
void LocalConvexResult::LocalShapeInfo::set(BulletSharp::LocalShapeInfo^ value)
{
	_localShapeInfo = value;
	_native->m_localShapeInfo = GetUnmanagedNullable(value);
}


ConvexResultCallback::ConvexResultCallback()
{
	_closestHitFraction = btScalar(1.0);
	_collisionFilterGroup = CollisionFilterGroups::DefaultFilter;
	_collisionFilterMask = CollisionFilterGroups::AllFilter;
}

bool ConvexResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	bool collides = (proxy0->CollisionFilterGroup & _collisionFilterMask) != CollisionFilterGroups::None;
	collides = collides && (_collisionFilterGroup & proxy0->CollisionFilterMask) != CollisionFilterGroups::None;
	return collides;
}

btScalar ConvexResultCallback::ClosestHitFraction::get()
{
	if (_native)
	{
		return _native->m_closestHitFraction;
	}
	return _closestHitFraction;
}
void ConvexResultCallback::ClosestHitFraction::set(btScalar value)
{
	if (_native)
	{
		_native->m_closestHitFraction = value;
	}
	else
	{
		_closestHitFraction = value;
	}
}

CollisionFilterGroups ConvexResultCallback::CollisionFilterGroup::get()
{
	return _collisionFilterGroup;
}
void ConvexResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_collisionFilterGroup = value;
}

CollisionFilterGroups ConvexResultCallback::CollisionFilterMask::get()
{
	return _collisionFilterMask;
}
void ConvexResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_collisionFilterMask = value;
}

bool ConvexResultCallback::HasHit::get()
{
	return ClosestHitFraction < btScalar(1.0);
}


ConvexResultCallbackWrapper::ConvexResultCallbackWrapper(BulletSharp::ConvexResultCallback^ callback)
{
	m_closestHitFraction = callback->ClosestHitFraction;
	callback->_native = this;
	_callback = GCHandle::Alloc(callback);
	_callbackPtr = GCHandleToVoidPtr(_callback);
}

ConvexResultCallbackWrapper::~ConvexResultCallbackWrapper()
{
	BulletSharp::ConvexResultCallback^ callback = static_cast<BulletSharp::ConvexResultCallback^>(_callback.Target);
	callback->_native = 0;
	callback->ClosestHitFraction = m_closestHitFraction;
	_callback.Free();
}

bool ConvexResultCallbackWrapper::needsCollision(btBroadphaseProxy* proxy0) const
{
	// const method cannot access this->GCHandle directly, use void pointer
	return static_cast<BulletSharp::ConvexResultCallback^>(VoidPtrToGCHandle(_callbackPtr).Target)->NeedsCollision(BroadphaseProxy::GetManaged(proxy0));
}

btScalar ConvexResultCallbackWrapper::addSingleResult(btCollisionWorld::LocalConvexResult& rayResult, bool normalInWorldSpace)
{
	return static_cast<BulletSharp::ConvexResultCallback^>(_callback.Target)->AddSingleResult(gcnew LocalConvexResult(&rayResult, true), normalInWorldSpace);
}


ClosestConvexResultCallback::ClosestConvexResultCallback()
{
}

ClosestConvexResultCallback::ClosestConvexResultCallback(Vector3% convexFromWorld,
	Vector3% convexToWorld)
{
	_convexFromWorld = convexFromWorld;
	_convexToWorld = convexToWorld;
}

#pragma managed(push, off)
void ClosestConvexResultCallback_AddSingleResult(btCollisionWorld::LocalConvexResult* convexResult, bool normalInWorldSpace,
	btVector3* hitNormalWorld)
{
	if (normalInWorldSpace)
	{
		*hitNormalWorld = convexResult->m_hitNormalLocal;
	}
	else
	{
		// need to transform normal into worldspace
		*hitNormalWorld = convexResult->m_hitCollisionObject->getWorldTransform().getBasis()*convexResult->m_hitNormalLocal;
	}
}
#pragma managed(pop)
btScalar ClosestConvexResultCallback::AddSingleResult(LocalConvexResult^ convexResult, bool normalInWorldSpace)
{
	//caller already does the filter on the ClosestHitFraction
	System::Diagnostics::Debug::Assert(convexResult->HitFraction <= ClosestHitFraction);

	ClosestHitFraction = convexResult->HitFraction;
	_hitCollisionObject = convexResult->HitCollisionObject;
	btVector3* hitNormalWorldTemp = ALIGNED_NEW(btVector3);
	ClosestConvexResultCallback_AddSingleResult(convexResult->_native, normalInWorldSpace,
		hitNormalWorldTemp);
	Math::BtVector3ToVector3(hitNormalWorldTemp, _hitNormalWorld);
	ALIGNED_FREE(hitNormalWorldTemp);
	_hitPointWorld = convexResult->HitPointLocal;
	return convexResult->HitFraction;
}

Vector3 ClosestConvexResultCallback::ConvexFromWorld::get()
{
	return _convexFromWorld;
}
void ClosestConvexResultCallback::ConvexFromWorld::set(Vector3 value)
{
	_convexFromWorld = value;
}

Vector3 ClosestConvexResultCallback::ConvexToWorld::get()
{
	return _convexToWorld;
}
void ClosestConvexResultCallback::ConvexToWorld::set(Vector3 value)
{
	_convexToWorld = value;
}

CollisionObject^ ClosestConvexResultCallback::HitCollisionObject::get()
{
	return _hitCollisionObject;
}
void ClosestConvexResultCallback::HitCollisionObject::set(CollisionObject^ value)
{
	_hitCollisionObject = value;
}

Vector3 ClosestConvexResultCallback::HitNormalWorld::get()
{
	return _hitNormalWorld;
}
void ClosestConvexResultCallback::HitNormalWorld::set(Vector3 value)
{
	_hitNormalWorld = value;
}

Vector3 ClosestConvexResultCallback::HitPointWorld::get()
{
	return _hitPointWorld;
}
void ClosestConvexResultCallback::HitPointWorld::set(Vector3 value)
{
	_hitPointWorld = value;
}


ClosestRayResultCallback::ClosestRayResultCallback()
{
}

ClosestRayResultCallback::ClosestRayResultCallback(Vector3% rayFromWorld,
	Vector3% rayToWorld)
{
	_rayFromWorld = rayFromWorld;
	_rayToWorld = rayToWorld;
}

btScalar ClosestRayResultCallback::AddSingleResult(LocalRayResult^ rayResult, bool normalInWorldSpace)
{
	//caller already does the filter on the ClosestHitFraction
	System::Diagnostics::Debug::Assert(rayResult->HitFraction <= ClosestHitFraction);

	ClosestHitFraction = rayResult->HitFraction;
	CollisionObject = rayResult->CollisionObject;
	btVector3* hitNormalWorldTemp = ALIGNED_NEW(btVector3);
	btVector3* hitPointWorldTemp = ALIGNED_NEW(btVector3);
	btVector3* rayFromWorld = Math::Vector3ToBtVector3(_rayFromWorld);
	btVector3* rayToWorld = Math::Vector3ToBtVector3(_rayToWorld);
	RayResultCallback_AddSingleResult(rayResult->_native, normalInWorldSpace,
		rayFromWorld, rayToWorld, hitNormalWorldTemp, hitPointWorldTemp);
	Math::BtVector3ToVector3(hitNormalWorldTemp, _hitNormalWorld);
	Math::BtVector3ToVector3(hitPointWorldTemp, _hitPointWorld);
	ALIGNED_FREE(hitNormalWorldTemp);
	ALIGNED_FREE(hitPointWorldTemp);
	ALIGNED_FREE(rayFromWorld);
	ALIGNED_FREE(rayToWorld);
	return rayResult->HitFraction;
}

Vector3 ClosestRayResultCallback::HitNormalWorld::get()
{
	return _hitNormalWorld;
}
void ClosestRayResultCallback::HitNormalWorld::set(Vector3 value)
{
	_hitNormalWorld = value;
}

Vector3 ClosestRayResultCallback::HitPointWorld::get()
{
	return _hitPointWorld;
}
void ClosestRayResultCallback::HitPointWorld::set(Vector3 value)
{
	_hitPointWorld = value;
}

Vector3 ClosestRayResultCallback::RayFromWorld::get()
{
	return _rayFromWorld;
}
void ClosestRayResultCallback::RayFromWorld::set(Vector3 value)
{
	_rayFromWorld = value;
}

Vector3 ClosestRayResultCallback::RayToWorld::get()
{
	return _rayToWorld;
}
void ClosestRayResultCallback::RayToWorld::set(Vector3 value)
{
	_rayToWorld = value;
}


ContactResultCallback::ContactResultCallback()
{
	_collisionFilterGroup = CollisionFilterGroups::DefaultFilter;
	_collisionFilterMask = CollisionFilterGroups::AllFilter;
}

bool ContactResultCallback::NeedsCollision(BroadphaseProxy^ proxy0)
{
	bool collides = (proxy0->CollisionFilterGroup & _collisionFilterMask) != CollisionFilterGroups::None;
	collides = collides && (_collisionFilterGroup & proxy0->CollisionFilterMask) != CollisionFilterGroups::None;
	return collides;
}

CollisionFilterGroups ContactResultCallback::CollisionFilterGroup::get()
{
	return _collisionFilterGroup;
}
void ContactResultCallback::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_collisionFilterGroup = value;
}

CollisionFilterGroups ContactResultCallback::CollisionFilterMask::get()
{
	return _collisionFilterMask;
}
void ContactResultCallback::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_collisionFilterMask = value;
}


#undef Callback
#define Callback static_cast<BulletSharp::ContactResultCallback^>(VoidPtrToGCHandle(_callback).Target)

ContactResultCallbackWrapper::ContactResultCallbackWrapper(BulletSharp::ContactResultCallback^ callback)
{
	_callback = GCHandleToVoidPtr(GCHandle::Alloc(callback, GCHandleType::Weak));
}

ContactResultCallbackWrapper::~ContactResultCallbackWrapper()
{
	VoidPtrToGCHandle(_callback).Free();
}

bool ContactResultCallbackWrapper::needsCollision(btBroadphaseProxy* proxy0) const
{
	return Callback->NeedsCollision(BroadphaseProxy::GetManaged(proxy0));
}

btScalar ContactResultCallbackWrapper::addSingleResult(btManifoldPoint& cp,
	const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
	const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	btScalar ret = Callback->AddSingleResult(gcnew ManifoldPoint(&cp, true),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);

	// Bullet may use temporary btTriangleShapes that can be destroyed before before non-deterministic disposal.
	// Check if these collision shapes were referenced in managed code and clean up any references here.
	btCollisionShape* collisionShape0 = (btCollisionShape*)colObj0Wrap->getCollisionShape();
	btCollisionShape* collisionShape1 = (btCollisionShape*)colObj1Wrap->getCollisionShape();
	
	if (collisionShape0->getUserPointer() &&
		collisionShape0->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj0Wrap->getCollisionObject()->getCollisionShape() != collisionShape0)
	{
		delete CollisionShape::GetManaged(collisionShape0);
		collisionShape0->setUserPointer(0);
	}
	if (collisionShape1->getUserPointer() &&
		collisionShape1->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj1Wrap->getCollisionObject()->getCollisionShape() != collisionShape1)
	{
		delete CollisionShape::GetManaged(collisionShape1);
		collisionShape1->setUserPointer(0);
	}

	return ret;
}


CollisionWorld::CollisionWorld(btCollisionWorld* native)
{
	if (!native) {
		return;
	}
	_native = native;
	_collisionObjectArray = gcnew AlignedCollisionObjectArray(&_native->getCollisionObjectArray(), native);
}

CollisionWorld::CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ broadphasePairCache,
	BulletSharp::CollisionConfiguration^ collisionConfiguration)
{
	_native = new btCollisionWorld(dispatcher->_native, broadphasePairCache->_native,
		collisionConfiguration->_native);
	_collisionObjectArray = gcnew AlignedCollisionObjectArray(&_native->getCollisionObjectArray(), _native);
	Dispatcher = dispatcher;
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

#ifndef DISABLE_DEBUGDRAW
	// Clear IDebugDraw wrapper
	DebugDrawer = nullptr;
	if (_dispatchInfo && _dispatchInfo->_debugDrawWrapper) {
		delete _dispatchInfo->_debugDrawWrapper;
		_dispatchInfo->_debugDrawWrapper = 0;
	}
#endif
	Dispatcher = nullptr;

#if _DEBUG
	if (_collisionObjectArray->_native == 0) {
		// Reference to this world has been lost and
		// _collisionObjectArray has been arbitrarily finalized by the GC.
		Console::WriteLine("!" + ToString() + "(): Warning: world is implicitly disposed!");
	}
	else if (_collisionObjectArray->Count != 0) {
		Console::WriteLine(
			"!" + ToString() + "(): {0} collision objects are still in the world!", _collisionObjectArray->Count);
	}

	if (_broadphase->IsDisposed) {
		//throw gcnew ObjectDisposedException("_broadphase",
		Console::WriteLine(
			"The BroadphaseInterface was disposed before the CollisionWorld. "
			"It is required for CollisionWorld cleanup, so dispose it later than the world.");
	}
#else
	if (_collisionObjectArray->_native != 0) {
		_collisionObjectArray->Clear();
	}
#endif

	if (_broadphase->IsDisposed) {
		return;
	}

	delete _native;
	_native = NULL;
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask)
{
	_collisionObjectArray->Add(collisionObject, (short)collisionFilterGroup, (short)collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject, short collisionFilterGroup, short collisionFilterMask)
{
	_collisionObjectArray->Add(collisionObject, collisionFilterGroup, collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject)
{
	_collisionObjectArray->Add(collisionObject);
}

void CollisionWorld::ComputeOverlappingPairs()
{
	_native->computeOverlappingPairs();
}

void CollisionWorld::ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB,
	ContactResultCallback^ resultCallback)
{
	ContactResultCallbackWrapper result = ContactResultCallbackWrapper(resultCallback);
	_native->contactPairTest(colObjA->_native, colObjB->_native, result);
}

void CollisionWorld::ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback)
{
	ContactResultCallbackWrapper result = ContactResultCallbackWrapper(resultCallback);
	_native->contactTest(colObj->_native, result);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to,
	ConvexResultCallback^ resultCallback, btScalar allowedCcdPenetration)
{
	TRANSFORM_CONV(from);
	TRANSFORM_CONV(to);
	ConvexResultCallbackWrapper result = ConvexResultCallbackWrapper(resultCallback);
	_native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(from),
		TRANSFORM_USE(to), result, allowedCcdPenetration);
	TRANSFORM_DEL(from);
	TRANSFORM_DEL(to);
}

void CollisionWorld::ConvexSweepTest(ConvexShape^ castShape, Matrix from, Matrix to,
	ConvexResultCallback^ resultCallback)
{
	TRANSFORM_CONV(from);
	TRANSFORM_CONV(to);
	ConvexResultCallbackWrapper result = ConvexResultCallbackWrapper(resultCallback);
	_native->convexSweepTest((btConvexShape*)castShape->_native, TRANSFORM_USE(from),
		TRANSFORM_USE(to), result);
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
	ConvexResultCallbackWrapper result = ConvexResultCallbackWrapper(resultCallback);
	btCollisionWorld::objectQuerySingle((btConvexShape*)castShape->_native, TRANSFORM_USE(rayFromTrans),
		TRANSFORM_USE(rayToTrans), collisionObject->_native, collisionShape->_native,
		TRANSFORM_USE(colObjWorldTransform), result, allowedPenetration);
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
	VECTOR3_CONV(rayFromWorld);
	VECTOR3_CONV(rayToWorld);
	_native->rayTest(VECTOR3_USE(rayFromWorld), VECTOR3_USE(rayToWorld), *resultCallback->_native);
	VECTOR3_DEL(rayFromWorld);
	VECTOR3_DEL(rayToWorld);
}

void CollisionWorld::RayTest(Vector3% rayFromWorld, Vector3% rayToWorld, RayResultCallback^ resultCallback)
{
	VECTOR3_CONV(rayFromWorld);
	VECTOR3_CONV(rayToWorld);
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
	_collisionObjectArray->Remove(collisionObject);
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
	return _collisionObjectArray;
}

#ifndef DISABLE_DEBUGDRAW
IDebugDraw^ CollisionWorld::DebugDrawer::get()
{
	return _debugDrawer;
}
void CollisionWorld::DebugDrawer::set(IDebugDraw^ debugDrawer)
{
	if (_debugDrawer)
	{
		if (_debugDrawer == debugDrawer) {
			return;
		}

		// Clear IDebugDraw wrapper
		if (!dynamic_cast<DebugDraw^>(_debugDrawer)) {
			delete _native->getDebugDrawer();
		}
	}

	_debugDrawer = debugDrawer;
	if (!debugDrawer) {
		_native->setDebugDrawer(0);
		return;
	}

	DebugDraw^ cast = dynamic_cast<DebugDraw^>(debugDrawer);
	if (cast != nullptr) {
		_native->setDebugDrawer(cast->_native);
	} else {
		// Create IDebugDraw wrapper, remember to delete it
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		_native->setDebugDrawer(wrapper);
	}
}
#endif

BulletSharp::Dispatcher^ CollisionWorld::Dispatcher::get()
{
	return _dispatcher;
}
// Internal setter, registers the world with the Dispatcher, for NearCallback parameters
void CollisionWorld::Dispatcher::set(BulletSharp::Dispatcher^ dispatcher)
{
	if (_dispatcher) {
		_dispatcher->_dispatcherInfoRefs->Remove(IntPtr(DispatchInfo->_native));
	}
	_dispatcher = dispatcher;
	if (dispatcher) {
		dispatcher->_dispatcherInfoRefs->Add(IntPtr(DispatchInfo->_native), DispatchInfo);
	}
}

DispatcherInfo^ CollisionWorld::DispatchInfo::get()
{
	if (!_dispatchInfo) {
		_dispatchInfo = gcnew DispatcherInfo(&_native->getDispatchInfo());
	}
	return _dispatchInfo;
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
	return Broadphase->OverlappingPairCache;
}
