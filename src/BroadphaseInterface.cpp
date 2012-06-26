#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"
#include "Collections.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

BroadphaseAabbCallback::BroadphaseAabbCallback(btBroadphaseAabbCallback* callback)
{
	_unmanaged = callback;
}

BroadphaseAabbCallback::BroadphaseAabbCallback()
{
	_unmanaged = new BroadphaseAabbCallbackWrapper(this);
}

BroadphaseAabbCallback::~BroadphaseAabbCallback()
{
	this->!BroadphaseAabbCallback();
}

BroadphaseAabbCallback::!BroadphaseAabbCallback()
{
	delete _unmanaged;
	_unmanaged = 0;
}

btBroadphaseAabbCallback* BroadphaseAabbCallback::UnmanagedPointer::get()
{
	return _unmanaged;
}
void BroadphaseAabbCallback::UnmanagedPointer::set(btBroadphaseAabbCallback* value)
{
	_unmanaged = value;
}


BroadphaseAabbCallbackWrapper::BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback)
{
	_aabbCallback = aabbCallback;
}

bool BroadphaseAabbCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return _aabbCallback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


BroadphaseRayCallback::BroadphaseRayCallback(BroadphaseRayCallbackWrapper* callback)
: BroadphaseAabbCallback(callback)
{
}

BroadphaseRayCallback::BroadphaseRayCallback()
: BroadphaseAabbCallback(0)
{
	_unmanaged = new BroadphaseRayCallbackWrapper(this);
}

btScalar BroadphaseRayCallback::LambdaMax::get()
{
	return ((btBroadphaseRayCallback*)_unmanaged)->m_lambda_max;
}
void BroadphaseRayCallback::LambdaMax::set(btScalar value)
{
	((btBroadphaseRayCallback*)_unmanaged)->m_lambda_max = value;
}

Vector3 BroadphaseRayCallback::RayDirectionInverse::get()
{
	return Math::BtVector3ToVector3(&((btBroadphaseRayCallback*)_unmanaged)->m_rayDirectionInverse);
}
void BroadphaseRayCallback::RayDirectionInverse::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &((btBroadphaseRayCallback*)_unmanaged)->m_rayDirectionInverse);
}

UIntArray^ BroadphaseRayCallback::Signs::get()
{
	return gcnew UIntArray(&((btBroadphaseRayCallback*)_unmanaged)->m_signs[0], 3);
}

btBroadphaseRayCallback* BroadphaseRayCallback::UnmanagedPointer::get()
{
	return (btBroadphaseRayCallback*)BroadphaseAabbCallback::UnmanagedPointer;
}


BroadphaseRayCallbackWrapper::BroadphaseRayCallbackWrapper(gcroot<BroadphaseRayCallback^> rayCallback)
{
	_rayCallback = rayCallback;
}

bool BroadphaseRayCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return _rayCallback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


BroadphaseInterface::BroadphaseInterface(btBroadphaseInterface* broadphase)
{
	_broadphase = broadphase;
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

	_broadphase = NULL;

	OnDisposed(this, nullptr);
}

bool BroadphaseInterface::IsDisposed::get()
{
	return (_broadphase == NULL);
}

void BroadphaseInterface::AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_broadphase->aabbTest(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), *callback->UnmanagedPointer);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::CalculateOverlappingPairs(Dispatcher^ dispatcher)
{
	_broadphase->calculateOverlappingPairs(dispatcher->UnmanagedPointer);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
	int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	btBroadphaseProxy* proxy = new btBroadphaseProxy;

	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	proxy = _broadphase->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		shapeType, userPtr.ToPointer(), (short int)collisionFilterGroup, (short int)collisionFilterMask,
		dispatcher->UnmanagedPointer, multiSapProxy.ToPointer());

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);

	return BroadphaseProxy::GetManaged(proxy);
}

void BroadphaseInterface::DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	_broadphase->destroyProxy(proxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::GetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	_broadphase->getAabb(proxy->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	_broadphase->getBroadphaseAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::PrintStats()
{
	_broadphase->printStats();
}

#pragma managed(push, off)
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo,
	btBroadphaseRayCallback* rayCallback)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback);
}
#pragma managed(pop)

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
								  Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_broadphase->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *rayCallback->UnmanagedPointer,
		VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);

	BroadphaseInterface_RayTest(_broadphase, VECTOR3_PTR(rayFrom), VECTOR3_PTR(rayTo), (btBroadphaseRayCallback*)rayCallback->_unmanaged);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void BroadphaseInterface::ResetPool(Dispatcher^ dispatcher)
{
	_broadphase->resetPool(dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_broadphase->setAabb(proxy->UnmanagedPointer, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->UnmanagedPointer);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	return dynamic_cast<BulletSharp::OverlappingPairCache^>(
		BulletSharp::OverlappingPairCache::GetManaged(_broadphase->getOverlappingPairCache()));
}

btBroadphaseInterface* BroadphaseInterface::UnmanagedPointer::get()
{
	return _broadphase;
}
void BroadphaseInterface::UnmanagedPointer::set(btBroadphaseInterface* value)
{
	_broadphase = value;
}
