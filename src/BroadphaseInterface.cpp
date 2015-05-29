#include "StdAfx.h"

#include "AxisSweep3.h"
#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"
#include "Collections.h"
#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "SimpleBroadphase.h"

BroadphaseAabbCallback::BroadphaseAabbCallback(btBroadphaseAabbCallback* native)
{
	_native = native;
}

BroadphaseAabbCallback::BroadphaseAabbCallback()
{
	_native = new BroadphaseAabbCallbackWrapper(this);
}

BroadphaseAabbCallback::~BroadphaseAabbCallback()
{
	this->!BroadphaseAabbCallback();
}

BroadphaseAabbCallback::!BroadphaseAabbCallback()
{
	delete _native;
	_native = NULL;
}


#define Callback static_cast<BroadphaseAabbCallback^>(VoidPtrToGCHandle(_aabbCallback).Target)

BroadphaseAabbCallbackWrapper::BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback)
{
	_aabbCallback = GCHandleToVoidPtr(GCHandle::Alloc(aabbCallback, GCHandleType::Weak));
}

BroadphaseAabbCallbackWrapper::~BroadphaseAabbCallbackWrapper()
{
	VoidPtrToGCHandle(_aabbCallback).Free();
}

bool BroadphaseAabbCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return Callback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


#define Native static_cast<btBroadphaseRayCallback*>(_native)

BroadphaseRayCallback::BroadphaseRayCallback(BroadphaseRayCallbackWrapper* native)
	: BroadphaseAabbCallback(native)
{
}

BroadphaseRayCallback::BroadphaseRayCallback()
	: BroadphaseAabbCallback(0)
{
	_native = new BroadphaseRayCallbackWrapper(GCHandleToVoidPtr(GCHandle::Alloc(this, GCHandleType::Weak)));
}

btScalar BroadphaseRayCallback::LambdaMax::get()
{
	return Native->m_lambda_max;
}
void BroadphaseRayCallback::LambdaMax::set(btScalar value)
{
	Native->m_lambda_max = value;
}

Vector3 BroadphaseRayCallback::RayDirectionInverse::get()
{
	return Math::BtVector3ToVector3(&Native->m_rayDirectionInverse);
}
void BroadphaseRayCallback::RayDirectionInverse::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_rayDirectionInverse);
}

UIntArray^ BroadphaseRayCallback::Signs::get()
{
	if (!_signs)
	{
		_signs = gcnew UIntArray(&Native->m_signs[0], 3);
	}
	return _signs;
}


#undef Callback
#define Callback static_cast<BroadphaseRayCallback^>(VoidPtrToGCHandle(_rayCallback).Target)

BroadphaseRayCallbackWrapper::BroadphaseRayCallbackWrapper(void* rayCallbackHandle)
{
	_rayCallback = rayCallbackHandle;
}

BroadphaseRayCallbackWrapper::~BroadphaseRayCallbackWrapper()
{
	VoidPtrToGCHandle(_rayCallback).Free();
}

bool BroadphaseRayCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return Callback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


BroadphaseInterface::BroadphaseInterface(btBroadphaseInterface* native)
{
	_native = native;
}

BroadphaseInterface::~BroadphaseInterface()
{
	this->!BroadphaseInterface();
}

BroadphaseInterface::!BroadphaseInterface()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

void BroadphaseInterface::AabbTestRef(Vector3% aabbMin, Vector3% aabbMax, BroadphaseAabbCallback^ callback)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->aabbTest(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), *(btBroadphaseRayCallback*)callback->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->aabbTest(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), *callback->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::CalculateOverlappingPairs(Dispatcher^ dispatcher)
{
	_native->calculateOverlappingPairs(dispatcher->_native);
}

void BroadphaseInterface::DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	_native->destroyProxy(proxy->_native, dispatcher->_native);
}

void BroadphaseInterface::GetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->getAabb(proxy->_native, *aabbMinTemp, *aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->getBroadphaseAabb(*aabbMinTemp, *aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void BroadphaseInterface::PrintStats()
{
	_native->printStats();
}

#pragma managed(push, off)
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo,
	btBroadphaseRayCallback* rayCallback)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback);
}
#pragma managed(pop)

void BroadphaseInterface::RayTestRef(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback,
	Vector3% aabbMin, Vector3% aabbMax)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *(btBroadphaseRayCallback*)rayCallback->_native,
		VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
	Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *(btBroadphaseRayCallback*)rayCallback->_native,
		VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::RayTestRef(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	BroadphaseInterface_RayTest(_native, VECTOR3_PTR(rayFrom), VECTOR3_PTR(rayTo), (btBroadphaseRayCallback*)rayCallback->_native);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	BroadphaseInterface_RayTest(_native, VECTOR3_PTR(rayFrom), VECTOR3_PTR(rayTo), (btBroadphaseRayCallback*)rayCallback->_native);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void BroadphaseInterface::ResetPool(Dispatcher^ dispatcher)
{
	_native->resetPool(dispatcher->_native);
}

void BroadphaseInterface::SetAabbRef(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax,
	Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->setAabb(proxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax,
	Dispatcher^ dispatcher)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->setAabb(proxy->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

bool BroadphaseInterface::IsDisposed::get()
{
	return (_native == NULL);
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	return _pairCache;
}
