#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionAlgorithm.h"
#include "CollisionObject.h"
#include "SimpleBroadphase.h"
#ifndef DISABLE_DBVT
#include "DbvtBroadphase.h"
#endif

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* native)
{
	UnmanagedPointer = native;
}

BroadphaseProxy::BroadphaseProxy()
{
	UnmanagedPointer = new btBroadphaseProxy();
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask,
	IntPtr multiSapParentProxy)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);

	_clientObject = userObject;

	UnmanagedPointer = new btBroadphaseProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask,
		multiSapParentProxy.ToPointer()
		);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);

	_clientObject = userObject;

	UnmanagedPointer = new btBroadphaseProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask
		);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BroadphaseProxy^ BroadphaseProxy::GetManaged(btBroadphaseProxy* broadphaseProxy)
{
	if (broadphaseProxy == 0)
		return nullptr;

	BroadphaseProxy^ proxy = GetObjectFromTable(BroadphaseProxy, broadphaseProxy);
	if (proxy != nullptr) {
		if (broadphaseProxy->getUid() == proxy->_uid) {
			return proxy;
		}
		ObjectTable::Remove(broadphaseProxy);
	}

#ifndef DISABLE_DBVT
	btDbvtProxy* dbvtProxy = static_cast<btDbvtProxy*>(broadphaseProxy);
	if (dbvtProxy)
	{
		proxy = gcnew DbvtProxy(dbvtProxy);
		proxy->_doesNotOwnObject = true;
		return proxy;
	}
#endif

	btSimpleBroadphaseProxy* simpleProxy = static_cast<btSimpleBroadphaseProxy*>(broadphaseProxy);
	if (simpleProxy)
	{
		proxy = gcnew SimpleBroadphaseProxy(simpleProxy);
		proxy->_doesNotOwnObject = true;
		return proxy;
	}

	proxy = gcnew BroadphaseProxy(broadphaseProxy);
	proxy->_doesNotOwnObject = true;
	return proxy;
}

bool BroadphaseProxy::IsCompound(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isCompound((int)proxyType);
}

bool BroadphaseProxy::IsConcave(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isConcave((int)proxyType);
}

bool BroadphaseProxy::IsConvex(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isConvex((int)proxyType);
}

bool BroadphaseProxy::IsConvex2D(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isConvex2d((int)proxyType);
}

bool BroadphaseProxy::IsInfinite(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isInfinite((int)proxyType);
}

bool BroadphaseProxy::IsNonMoving(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isNonMoving((int)proxyType);
}

bool BroadphaseProxy::IsPolyhedral(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isPolyhedral((int)proxyType);
}

bool BroadphaseProxy::IsSoftBody(BroadphaseNativeType proxyType)
{
	return btBroadphaseProxy::isSoftBody((int)proxyType);
}

Vector3 BroadphaseProxy::AabbMax::get()
{
	return Math::BtVector3ToVector3(&_native->m_aabbMax);
}
void BroadphaseProxy::AabbMax::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_aabbMax);
}

Vector3 BroadphaseProxy::AabbMin::get()
{
	return Math::BtVector3ToVector3(&_native->m_aabbMin);
}
void BroadphaseProxy::AabbMin::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_aabbMin);
}

Object^ BroadphaseProxy::ClientObject::get()
{
	if (_native->m_clientObject)
	{
		_clientObject = CollisionObject::GetManaged((btCollisionObject*)_native->m_clientObject);
	}

	return _clientObject;
}
void BroadphaseProxy::ClientObject::set(Object^ value)
{
	_clientObject = value;
}

CollisionFilterGroups BroadphaseProxy::CollisionFilterGroup::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterGroup;
}
void BroadphaseProxy::CollisionFilterGroup::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterGroup = (short int)value;
}

CollisionFilterGroups BroadphaseProxy::CollisionFilterMask::get()
{
	return (CollisionFilterGroups)_native->m_collisionFilterMask;
}
void BroadphaseProxy::CollisionFilterMask::set(CollisionFilterGroups value)
{
	_native->m_collisionFilterMask = (short int)value;
}

IntPtr BroadphaseProxy::MultiSapParentProxy::get()
{
	return IntPtr(_native->m_multiSapParentProxy);
}
void BroadphaseProxy::MultiSapParentProxy::set(IntPtr value)
{
	_native->m_multiSapParentProxy = value.ToPointer();
}

int BroadphaseProxy::UniqueID::get()
{
	return _native->getUid();
}
void BroadphaseProxy::UniqueID::set(int value)
{
	_uid = value;
	_native->m_uniqueId = value;
}

btBroadphaseProxy* BroadphaseProxy::UnmanagedPointer::get()
{
	return _native;
}
void BroadphaseProxy::UnmanagedPointer::set(btBroadphaseProxy* value)
{
	_native = value;
	ObjectTable::Add(this, _native);
}


BroadphasePair::BroadphasePair(btBroadphasePair* pair)
{
	_native = pair;
}
/*
BroadphasePair::BroadphasePair()
{
	_native = new btBroadphasePair();
}

BroadphasePair::BroadphasePair(BroadphasePair^ pair)
{
	_native = pair->_native;
}

BroadphasePair::BroadphasePair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	_native = new btBroadphasePair(*proxy0->_native, *proxy1->_native);
}
*/
CollisionAlgorithm^ BroadphasePair::Algorithm::get()
{
	return CollisionAlgorithm::GetManaged(_native->m_algorithm);
}
void BroadphasePair::Algorithm::set(CollisionAlgorithm^ value)
{
	_native->m_algorithm = GetUnmanagedNullable(value);
}

BroadphaseProxy^ BroadphasePair::Proxy0::get()
{
	return BroadphaseProxy::GetManaged(_native->m_pProxy0);
}
void BroadphasePair::Proxy0::set(BroadphaseProxy^ value)
{
	_native->m_pProxy0 = GetUnmanagedNullable(value);
}

BroadphaseProxy^ BroadphasePair::Proxy1::get()
{
	return BroadphaseProxy::GetManaged(_native->m_pProxy1);
}
void BroadphasePair::Proxy1::set(BroadphaseProxy^ value)
{
	_native->m_pProxy1 = GetUnmanagedNullable(value);
}
