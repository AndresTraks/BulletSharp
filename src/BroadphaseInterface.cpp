#include "StdAfx.h"

#include "AxisSweep3.h"
#include "BroadphaseProxy.h"
#include "BroadphaseInterface.h"
#include "Collections.h"
#include "DbvtBroadphase.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "SimpleBroadphase.h"

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


BroadphaseAabbCallbackWrapper::BroadphaseAabbCallbackWrapper(BroadphaseAabbCallback^ aabbCallback)
{
	_aabbCallback = aabbCallback;
}

bool BroadphaseAabbCallbackWrapper::process(const btBroadphaseProxy* proxy)
{
	return _aabbCallback->Process(BroadphaseProxy::GetManaged((btBroadphaseProxy*)proxy));
}


#define Unmanaged static_cast<btBroadphaseRayCallback*>(_unmanaged)

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
	return Unmanaged->m_lambda_max;
}
void BroadphaseRayCallback::LambdaMax::set(btScalar value)
{
	Unmanaged->m_lambda_max = value;
}

Vector3 BroadphaseRayCallback::RayDirectionInverse::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->m_rayDirectionInverse);
}
void BroadphaseRayCallback::RayDirectionInverse::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Unmanaged->m_rayDirectionInverse);
}

UIntArray^ BroadphaseRayCallback::Signs::get()
{
	return gcnew UIntArray(&Unmanaged->m_signs[0], 3);
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
	_unmanaged = broadphase;
}

BroadphaseInterface^ BroadphaseInterface::GetManaged(btBroadphaseInterface* broadphase)
{
	if (broadphase == 0)
		return nullptr;

	btAxisSweep3* axisSweep = static_cast<btAxisSweep3*>(broadphase);
	if (axisSweep)
	{
		return gcnew AxisSweep3(axisSweep);
	}

	btDbvtBroadphase* dbvt = static_cast<btDbvtBroadphase*>(broadphase);
	if (dbvt)
	{
		return gcnew DbvtBroadphase(dbvt);
	}

	bt32BitAxisSweep3* axisSweep32 = static_cast<bt32BitAxisSweep3*>(broadphase);
	if (axisSweep32)
	{
		return gcnew AxisSweep3_32Bit(axisSweep32);
	}

	btSimpleBroadphase* simple = static_cast<btSimpleBroadphase*>(broadphase);
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

	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

bool BroadphaseInterface::IsDisposed::get()
{
	return (_unmanaged == NULL);
}

void BroadphaseInterface::AabbTest(Vector3 aabbMin, Vector3 aabbMax, BroadphaseAabbCallback^ callback)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_unmanaged->aabbTest(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), *(btBroadphaseRayCallback*)callback->_unmanaged);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BroadphaseInterface::CalculateOverlappingPairs(Dispatcher^ dispatcher)
{
	_unmanaged->calculateOverlappingPairs(dispatcher->_unmanaged);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
	int shapeType, IntPtr userPtr, CollisionFilterGroups collisionFilterGroup,
	CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy)
{
	btBroadphaseProxy* proxy = new btBroadphaseProxy;

	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	proxy = _unmanaged->createProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax),
		shapeType, userPtr.ToPointer(), (short int)collisionFilterGroup, (short int)collisionFilterMask,
		dispatcher->_unmanaged, multiSapProxy.ToPointer());

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);

	return BroadphaseProxy::GetManaged(proxy);
}

void BroadphaseInterface::DestroyProxy(BroadphaseProxy^ proxy, Dispatcher^ dispatcher)
{
	_unmanaged->destroyProxy(proxy->_unmanaged, dispatcher->_unmanaged);
}

void BroadphaseInterface::GetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	_unmanaged->getAabb(proxy->_unmanaged, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;

	_unmanaged->getBroadphaseAabb(*aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void BroadphaseInterface::PrintStats()
{
	_unmanaged->printStats();
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

	_unmanaged->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *(btBroadphaseRayCallback*)rayCallback->_unmanaged,
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

	BroadphaseInterface_RayTest(_unmanaged, VECTOR3_PTR(rayFrom), VECTOR3_PTR(rayTo), (btBroadphaseRayCallback*)rayCallback->_unmanaged);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void BroadphaseInterface::ResetPool(Dispatcher^ dispatcher)
{
	_unmanaged->resetPool(dispatcher->_unmanaged);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_unmanaged->setAabb(proxy->_unmanaged, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), dispatcher->_unmanaged);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	return dynamic_cast<BulletSharp::OverlappingPairCache^>(
		BulletSharp::OverlappingPairCache::GetManaged(_unmanaged->getOverlappingPairCache()));
}
