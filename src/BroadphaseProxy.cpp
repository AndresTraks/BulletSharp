#include "StdAfx.h"

#include "BroadphaseProxy.h"

BroadphaseProxy::BroadphaseProxy()
{
	_proxy = new btBroadphaseProxy();
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask,
	IntPtr multiSapParentProxy)
{
	_proxy = new btBroadphaseProxy(
		*Math::Vector3ToBtVec3(aabbMin),
		*Math::Vector3ToBtVec3(aabbMax),
		userPtr.ToPointer(),
		(short int)collisionFilterGroup,
		(short int)collisionFilterMask,
		multiSapParentProxy.ToPointer()
	);
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask)
{
	_proxy = new btBroadphaseProxy(
		*Math::Vector3ToBtVec3(aabbMin),
		*Math::Vector3ToBtVec3(aabbMax),
		userPtr.ToPointer(),
		(short int)collisionFilterGroup,
		(short int)collisionFilterMask
	);
}

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* proxy)
{
	_proxy = proxy;
}

Vector3 BroadphaseProxy::AabbMin::get()
{
	return Math::BtVec3ToVector3(&_proxy->m_aabbMin);
}
void BroadphaseProxy::AabbMin::set(Vector3 value)
{
	Math::Vector3ToBtVec3(value, &_proxy->m_aabbMin);
}

Vector3 BroadphaseProxy::AabbMax::get()
{
	return Math::BtVec3ToVector3(&_proxy->m_aabbMax);
}
void BroadphaseProxy::AabbMax::set(Vector3 value)
{
	Math::Vector3ToBtVec3(value, &_proxy->m_aabbMax);
}

IntPtr BroadphaseProxy::ClientObject::get()
{
	return IntPtr(_proxy->m_clientObject);
}
void BroadphaseProxy::ClientObject::set(IntPtr value)
{
	_proxy->m_clientObject = value.ToPointer();
}

BulletSharp::CollisionFilterGroups BroadphaseProxy::CollisionFilterGroup::get()
{
	return (BulletSharp::CollisionFilterGroups)_proxy->m_collisionFilterGroup;
}
void BroadphaseProxy::CollisionFilterGroup::set(BulletSharp::CollisionFilterGroups value)
{
	_proxy->m_collisionFilterGroup = (short int)value;
}

BulletSharp::CollisionFilterGroups BroadphaseProxy::CollisionFilterMask::get()
{
	return (BulletSharp::CollisionFilterGroups)_proxy->m_collisionFilterMask;
}
void BroadphaseProxy::CollisionFilterMask::set(BulletSharp::CollisionFilterGroups value)
{
	_proxy->m_collisionFilterMask = (short int)value;
}

IntPtr BroadphaseProxy::MultiSapParentProxy::get()
{
	return IntPtr(_proxy->m_multiSapParentProxy);
}
void BroadphaseProxy::MultiSapParentProxy::set(IntPtr value)
{
	_proxy->m_multiSapParentProxy = value.ToPointer();
}

int BroadphaseProxy::Uid::get()
{
	return _proxy->getUid();
}
void BroadphaseProxy::Uid::set(int value)
{
	_proxy->m_uniqueId = value;
}

bool BroadphaseProxy::IsCompound(int proxyType)
{
	return _proxy->isCompound(proxyType);
}

bool BroadphaseProxy::IsConcave(int proxyType)
{
	return _proxy->isConcave(proxyType);
}

bool BroadphaseProxy::IsConvex(int proxyType)
{
	return _proxy->isConvex(proxyType);
}

bool BroadphaseProxy::IsConvex2d(int proxyType)
{
	return _proxy->isConvex2d(proxyType);
}

bool BroadphaseProxy::IsInfinite(int proxyType)
{
	return _proxy->isInfinite(proxyType);
}

bool BroadphaseProxy::IsPolyhedral(int proxyType)
{
	return _proxy->isPolyhedral(proxyType);
}

bool BroadphaseProxy::IsSoftBody(int proxyType)
{
	return _proxy->isSoftBody(proxyType);
}

btBroadphaseProxy* BroadphaseProxy::UnmanagedPointer::get()
{
	return _proxy;
}
void BroadphaseProxy::UnmanagedPointer::set(btBroadphaseProxy* value)
{
	_proxy = value;
}
