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


BroadphaseAabbCallbackWrapper::BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback)
{
	_aabbCallback = aabbCallback;
}

bool BroadphaseAabbCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return _aabbCallback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


#define Native static_cast<btBroadphaseRayCallback*>(_native)

BroadphaseRayCallback::BroadphaseRayCallback(BroadphaseRayCallbackWrapper* native)
	: BroadphaseAabbCallback(native)
{
}

BroadphaseRayCallback::BroadphaseRayCallback()
	: BroadphaseAabbCallback(0)
{
	_native = new BroadphaseRayCallbackWrapper(this);
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
	return gcnew UIntArray(&Native->m_signs[0], 3);
}


BroadphaseRayCallbackWrapper::BroadphaseRayCallbackWrapper(gcroot<BroadphaseRayCallback^> rayCallback)
{
	_rayCallback = rayCallback;
}

bool BroadphaseRayCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return _rayCallback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


BroadphaseInterface::BroadphaseInterface(btBroadphaseInterface* native)
{
	_native = native;
}

BroadphaseInterface^ BroadphaseInterface::GetManaged(btBroadphaseInterface* broadphase)
{
	if (broadphase == 0)
		return nullptr;

	btAxisSweep3* axisSweep = dynamic_cast<btAxisSweep3*>(broadphase);
	if (axisSweep)
	{
		return gcnew AxisSweep3(axisSweep);
	}

	btDbvtBroadphase* dbvt = dynamic_cast<btDbvtBroadphase*>(broadphase);
	if (dbvt)
	{
		return gcnew DbvtBroadphase(dbvt);
	}

	bt32BitAxisSweep3* axisSweep32 = dynamic_cast<bt32BitAxisSweep3*>(broadphase);
	if (axisSweep32)
	{
		return gcnew AxisSweep3_32Bit(axisSweep32);
	}

	btSimpleBroadphase* simple = dynamic_cast<btSimpleBroadphase*>(broadphase);
	if (simple)
	{
		return gcnew SimpleBroadphase(simple);
	}

	return gcnew BroadphaseInterface(broadphase);
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

bool BroadphaseInterface::IsDisposed::get()
{
	return (_native == NULL);
}

void BroadphaseInterface::AabbTest(Vector3% aabbMin, Vector3% aabbMax, BroadphaseAabbCallback^ callback)
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
	_native->aabbTest(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), *(btBroadphaseRayCallback*)callback->_native);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::CalculateOverlappingPairs(Dispatcher^ dispatcher)
{
	_native->calculateOverlappingPairs(dispatcher->_native);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
	int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btBroadphaseProxy* proxy = _native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		shapeType, userPtr.ToPointer(), (short int)collisionFilterGroup, (short int)collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return BroadphaseProxy::GetManaged(proxy);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
	int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	btBroadphaseProxy* ret = _native->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		shapeType, userPtr.ToPointer(), (short int)collisionFilterGroup, (short int)collisionFilterMask,
		dispatcher->_native, multiSapProxy.ToPointer());
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
	return BroadphaseProxy::GetManaged(ret);
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

void BroadphaseInterface::RayTest(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback,
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

void BroadphaseInterface::RayTest(Vector3% rayFrom, Vector3% rayTo, BroadphaseRayCallback^ rayCallback)
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

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax,
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

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	if (_pairCache == nullptr)
	{
		_pairCache = dynamic_cast<BulletSharp::OverlappingPairCache^>(
			BulletSharp::OverlappingPairCache::GetManaged(_native->getOverlappingPairCache()));
	}
	return _pairCache;
}
