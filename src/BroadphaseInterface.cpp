#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

BroadphaseAabbCallback::BroadphaseAabbCallback(btBroadphaseAabbCallback* callback)
{
	_aabbCallback = callback;
}

bool BroadphaseAabbCallback::Process(BroadphaseProxy^ proxy)
{
	return UnmanagedPointer->process(proxy->UnmanagedPointer);
}

btBroadphaseAabbCallback* BroadphaseAabbCallback::UnmanagedPointer::get()
{
	return _aabbCallback;
}
void BroadphaseAabbCallback::UnmanagedPointer::set(btBroadphaseAabbCallback* value)
{
	_aabbCallback = value;
}


BroadphaseRayCallback::BroadphaseRayCallback(btBroadphaseRayCallback* callback)
: BroadphaseAabbCallback(callback)
{
}

btBroadphaseRayCallback* BroadphaseRayCallback::UnmanagedPointer::get()
{
	return (btBroadphaseRayCallback*)BroadphaseAabbCallback::UnmanagedPointer;;
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

	OnDisposing( this, nullptr );

	_broadphase = NULL;

	OnDisposed( this, nullptr );
}

bool BroadphaseInterface::IsDisposed::get()
{
	return (_broadphase == NULL);
}

void BroadphaseInterface::AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_broadphase->aabbTest(*aabbMinTemp, *aabbMaxTemp, *callback->UnmanagedPointer);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::CalculateOverlappingPairs(Dispatcher^ dispatcher)
{
	_broadphase->calculateOverlappingPairs(dispatcher->UnmanagedPointer);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
	int shapeType, IntPtr userPtr, short int collisionFilterGroup,
	short int collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	btBroadphaseProxy* proxy = new btBroadphaseProxy;

	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	proxy = _broadphase->createProxy(*aabbMinTemp, *aabbMaxTemp,
		shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->UnmanagedPointer, multiSapProxy.ToPointer());

	delete aabbMinTemp;
	delete aabbMaxTemp;

	return gcnew BroadphaseProxy(proxy);
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

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	_broadphase->getBroadphaseAabb(*aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::PrintStats()
{
	_broadphase->printStats();
}

#pragma managed(push, off)
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo,
	btBroadphaseRayCallback* rayCallback, btVector3* aabbMin)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback, *aabbMin);
}
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo,
	btBroadphaseRayCallback* rayCallback)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback);
}
#pragma managed(pop)

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
								  Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_broadphase->rayTest(*rayFromTemp, *rayToTemp, *rayCallback->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete rayFromTemp;
	delete rayToTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback, Vector3 aabbMin)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);

	BroadphaseInterface_RayTest(_broadphase, rayFromTemp, rayToTemp, rayCallback->UnmanagedPointer, aabbMinTemp);

	delete rayFromTemp;
	delete rayToTemp;
	delete aabbMinTemp;
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback)
{
	btVector3* rayFromTemp = Math::Vector3ToBtVector3(rayFrom);
	btVector3* rayToTemp = Math::Vector3ToBtVector3(rayTo);

	BroadphaseInterface_RayTest(_broadphase, rayFromTemp, rayToTemp, rayCallback->UnmanagedPointer);

	delete rayFromTemp;
	delete rayToTemp;
}

void BroadphaseInterface::ResetPool(Dispatcher^ dispatcher)
{
	_broadphase->resetPool(dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_broadphase->setAabb(proxy->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp, dispatcher->UnmanagedPointer);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	btOverlappingPairCache* cache = _broadphase->getOverlappingPairCache();
	if (cache == 0)
		return nullptr;
	
	if (_pairCache == nullptr || _pairCache->UnmanagedPointer != cache)
		_pairCache = gcnew BulletSharp::OverlappingPairCache(cache);
	
	return _pairCache;
}

btBroadphaseInterface* BroadphaseInterface::UnmanagedPointer::get()
{
	return _broadphase;
}
void BroadphaseInterface::UnmanagedPointer::set(btBroadphaseInterface* value)
{
	_broadphase = value;
}
