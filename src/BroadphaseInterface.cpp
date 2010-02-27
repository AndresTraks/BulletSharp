#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"
#include "Dispatcher.h"

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
	if( this->IsDisposed == true )
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
	_broadphase->aabbTest(*Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMin), *callback->UnmanagedPointer);
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
	proxy = _broadphase->createProxy(*Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMax),
		shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->UnmanagedPointer, multiSapProxy.ToPointer());
	return gcnew BroadphaseProxy(proxy);
}

void BroadphaseInterface::DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	_broadphase->destroyProxy(proxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::GetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_broadphase->getAabb(proxy->UnmanagedPointer, *tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_broadphase->getBroadphaseAabb(*tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);
}

void BroadphaseInterface::PrintStats()
{
	_broadphase->printStats();
}

#pragma managed(push, off)
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo, btBroadphaseRayCallback* rayCallback,
	btVector3* aabbMin, btVector3* aabbMax)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback, *aabbMin, *aabbMax);
}
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo, btBroadphaseRayCallback* rayCallback,
	btVector3* aabbMin)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback, *aabbMin);
}
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo, btBroadphaseRayCallback* rayCallback)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback);
}
#pragma managed(pop)

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
	Vector3 aabbMin, Vector3 aabbMax)
{
	BroadphaseInterface_RayTest(_broadphase, Math::Vector3ToBtVec3(rayFrom), Math::Vector3ToBtVec3(rayTo),
		rayCallback->UnmanagedPointer, Math::Vector3ToBtVec3(aabbMin), Math::Vector3ToBtVec3(aabbMax));
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback,
	Vector3 aabbMin)
{
	BroadphaseInterface_RayTest(_broadphase, Math::Vector3ToBtVec3(rayFrom), Math::Vector3ToBtVec3(rayTo),
		rayCallback->UnmanagedPointer, Math::Vector3ToBtVec3(aabbMin));
}

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback)
{
	BroadphaseInterface_RayTest(_broadphase, Math::Vector3ToBtVec3(rayFrom), Math::Vector3ToBtVec3(rayTo),
		rayCallback->UnmanagedPointer);
}

void BroadphaseInterface::ResetPool(Dispatcher^ dispatcher)
{
	_broadphase->resetPool(dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	_broadphase->setAabb(proxy->UnmanagedPointer, *Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMax), dispatcher->UnmanagedPointer);
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
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
