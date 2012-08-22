#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionAlgorithm.h"
#include "CollisionObject.h"
#include "SimpleBroadphase.h"
#ifndef DISABLE_DBVT
#include "DbvtBroadphase.h"
#endif

BroadphaseProxy::BroadphaseProxy()
{
	UnmanagedPointer = new btBroadphaseProxy();
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask,
	IntPtr multiSapParentProxy)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_clientObject = userObject;

	UnmanagedPointer = new btBroadphaseProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask,
		multiSapParentProxy.ToPointer()
		);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, Object^ userObject,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	_clientObject = userObject;

	UnmanagedPointer = new btBroadphaseProxy(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), 0,
		(short int)collisionFilterGroup, (short int)collisionFilterMask
		);

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* proxy)
{
	UnmanagedPointer = proxy;
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

Vector3 BroadphaseProxy::AabbMin::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_aabbMin);
}
void BroadphaseProxy::AabbMin::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_aabbMin);
}

Vector3 BroadphaseProxy::AabbMax::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_aabbMax);
}
void BroadphaseProxy::AabbMax::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_aabbMax);
}

Object^ BroadphaseProxy::ClientObject::get()
{
	if (_unmanaged->m_clientObject)
	{
		_clientObject = CollisionObject::GetManaged((btCollisionObject*)_unmanaged->m_clientObject);
	}

	return _clientObject;
}
void BroadphaseProxy::ClientObject::set(Object^ value)
{
	_clientObject = value;
}

BulletSharp::CollisionFilterGroups BroadphaseProxy::CollisionFilterGroup::get()
{
	return (BulletSharp::CollisionFilterGroups)_unmanaged->m_collisionFilterGroup;
}
void BroadphaseProxy::CollisionFilterGroup::set(BulletSharp::CollisionFilterGroups value)
{
	_unmanaged->m_collisionFilterGroup = (short int)value;
}

BulletSharp::CollisionFilterGroups BroadphaseProxy::CollisionFilterMask::get()
{
	return (BulletSharp::CollisionFilterGroups)_unmanaged->m_collisionFilterMask;
}
void BroadphaseProxy::CollisionFilterMask::set(BulletSharp::CollisionFilterGroups value)
{
	_unmanaged->m_collisionFilterMask = (short int)value;
}

IntPtr BroadphaseProxy::MultiSapParentProxy::get()
{
	return IntPtr(_unmanaged->m_multiSapParentProxy);
}
void BroadphaseProxy::MultiSapParentProxy::set(IntPtr value)
{
	_unmanaged->m_multiSapParentProxy = value.ToPointer();
}

int BroadphaseProxy::Uid::get()
{
	return _unmanaged->getUid();
}
void BroadphaseProxy::Uid::set(int value)
{
	_uid = value;
	_unmanaged->m_uniqueId = value;
}

bool BroadphaseProxy::IsCompound(int proxyType)
{
	return btBroadphaseProxy::isCompound(proxyType);
}

bool BroadphaseProxy::IsConcave(int proxyType)
{
	return btBroadphaseProxy::isConcave(proxyType);
}

bool BroadphaseProxy::IsConvex(int proxyType)
{
	return btBroadphaseProxy::isConvex(proxyType);
}

bool BroadphaseProxy::IsConvex2d(int proxyType)
{
	return btBroadphaseProxy::isConvex2d(proxyType);
}

bool BroadphaseProxy::IsInfinite(int proxyType)
{
	return btBroadphaseProxy::isInfinite(proxyType);
}

bool BroadphaseProxy::IsPolyhedral(int proxyType)
{
	return btBroadphaseProxy::isPolyhedral(proxyType);
}

bool BroadphaseProxy::IsSoftBody(int proxyType)
{
	return btBroadphaseProxy::isSoftBody(proxyType);
}

btBroadphaseProxy* BroadphaseProxy::UnmanagedPointer::get()
{
	return _unmanaged;
}
void BroadphaseProxy::UnmanagedPointer::set(btBroadphaseProxy* value)
{
	_unmanaged = value;
	ObjectTable::Add(this, _unmanaged);
}


BroadphasePair::BroadphasePair(btBroadphasePair* pair)
{
	_pair = pair;
}

BroadphasePair::BroadphasePair()
{
	_pair = new btBroadphasePair();
}

BroadphasePair::BroadphasePair(BroadphasePair^ pair)
{
	_pair = pair->UnmanagedPointer;
}

BroadphasePair::BroadphasePair(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1)
{
	_pair = new btBroadphasePair(*proxy0->_unmanaged, *proxy1->_unmanaged);
}

CollisionAlgorithm^ BroadphasePair::Algorithm::get()
{
	return gcnew CollisionAlgorithm(_pair->m_algorithm);
}
void BroadphasePair::Algorithm::set(CollisionAlgorithm^ value)
{
	_pair->m_algorithm = value->UnmanagedPointer;
}

BroadphaseProxy^ BroadphasePair::Proxy0::get()
{
	return BroadphaseProxy::GetManaged(UnmanagedPointer->m_pProxy0);
}
void BroadphasePair::Proxy0::set(BroadphaseProxy^ value)
{
	if (value == nullptr)
		_pair->m_pProxy0 = nullptr;
	else
		_pair->m_pProxy0 = value->_unmanaged;
}

BroadphaseProxy^ BroadphasePair::Proxy1::get()
{
	return BroadphaseProxy::GetManaged(UnmanagedPointer->m_pProxy1);
}
void BroadphasePair::Proxy1::set(BroadphaseProxy^ value)
{
	if (value == nullptr)
		_pair->m_pProxy1 = nullptr;
	else
		_pair->m_pProxy1 = value->_unmanaged;
}

btBroadphasePair* BroadphasePair::UnmanagedPointer::get()
{
	return _pair;
}
void BroadphasePair::UnmanagedPointer::set(btBroadphasePair* pair)
{
	_pair = pair;
}
