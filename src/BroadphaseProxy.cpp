#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionAlgorithm.h"

BroadphaseProxy::BroadphaseProxy()
{
	_proxy = new btBroadphaseProxy();
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask,
	IntPtr multiSapParentProxy)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_proxy = new btBroadphaseProxy(*aabbMinTemp, *aabbMaxTemp, userPtr.ToPointer(),
		(short int)collisionFilterGroup, (short int)collisionFilterMask,
		multiSapParentProxy.ToPointer()
	);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
	BulletSharp::CollisionFilterGroups collisionFilterGroup,
	BulletSharp::CollisionFilterGroups collisionFilterMask)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_proxy = new btBroadphaseProxy(*aabbMinTemp, *aabbMaxTemp, userPtr.ToPointer(),
		(short int)collisionFilterGroup, (short int)collisionFilterMask
	);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* proxy)
{
	_proxy = proxy;
}

Vector3 BroadphaseProxy::AabbMin::get()
{
	return Math::BtVector3ToVector3(&_proxy->m_aabbMin);
}
void BroadphaseProxy::AabbMin::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_proxy->m_aabbMin);
}

Vector3 BroadphaseProxy::AabbMax::get()
{
	return Math::BtVector3ToVector3(&_proxy->m_aabbMax);
}
void BroadphaseProxy::AabbMax::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_proxy->m_aabbMax);
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
	_pair = new btBroadphasePair(*proxy0->UnmanagedPointer, *proxy1->UnmanagedPointer);
	_proxy0 = proxy0;
	_proxy1 = proxy1;
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
	if (_proxy0 == nullptr)
	{
		if (UnmanagedPointer->m_pProxy0 != nullptr)
			_proxy0 = gcnew BroadphaseProxy(UnmanagedPointer->m_pProxy0);
	}
	return _proxy0;
}
void BroadphasePair::Proxy0::set(BroadphaseProxy^ value)
{
	_proxy0 = value;
	
	if (_proxy0 == nullptr)
		_pair->m_pProxy0 = nullptr;
	else
		_pair->m_pProxy0 = _proxy0->UnmanagedPointer;
}

BroadphaseProxy^ BroadphasePair::Proxy1::get()
{
	if (_proxy1 == nullptr)
	{
		if (UnmanagedPointer->m_pProxy1 != nullptr)
			_proxy1 = gcnew BroadphaseProxy(UnmanagedPointer->m_pProxy1);
	}
	return _proxy1;
}
void BroadphasePair::Proxy1::set(BroadphaseProxy^ value)
{
	_proxy1 = value;
	
	if (_proxy1 == nullptr)
		_pair->m_pProxy1 = nullptr;
	else
		_pair->m_pProxy1 = _proxy0->UnmanagedPointer;
}

btBroadphasePair* BroadphasePair::UnmanagedPointer::get()
{
	return _pair;
}
void BroadphasePair::UnmanagedPointer::set(btBroadphasePair* pair)
{
	_pair = pair;
}
