#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionAlgorithm.h"
#include "CollisionObject.h"

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* native)
{
	_uid = native->getUid();
	_native = native;
}

BroadphaseProxy^ BroadphaseProxy::GetManaged(btBroadphaseProxy* broadphaseProxy)
{
	if (broadphaseProxy == 0)
		return nullptr;

	if (broadphaseProxy->m_clientObject) {
		CollisionObject^ clientObject = CollisionObject::GetManaged((btCollisionObject*)broadphaseProxy->m_clientObject);
		return clientObject->BroadphaseHandle;
	}

	throw gcnew InvalidOperationException("Unknown broadphase proxy!");
	//return gcnew BroadphaseProxy(broadphaseProxy);
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
	CollisionObject^ collisionObject = dynamic_cast<CollisionObject^>(value);
	if (collisionObject)
	{
		_native->m_clientObject = collisionObject->_native;
	}
	else if (value == nullptr)
	{
		_native->m_clientObject = 0;
	}
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


BroadphasePair::BroadphasePair(btBroadphasePair* native)
{
	_native = native;
}

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
