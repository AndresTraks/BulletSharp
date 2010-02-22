#include "StdAfx.h"

#include "BroadphaseProxy.h"

BroadphaseProxy::BroadphaseProxy()
{
	_proxy = new btBroadphaseProxy();
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax,
	IntPtr userPtr, short int collisionFilterGroup,
	short int collisionFilterMask,
	IntPtr multiSapParentProxy)
{
	_proxy = new btBroadphaseProxy(
		*Math::Vector3ToBtVec3(aabbMin),
		*Math::Vector3ToBtVec3(aabbMax),
		userPtr.ToPointer(),
		collisionFilterGroup,
		collisionFilterMask,
		multiSapParentProxy.ToPointer()
	);
}

BroadphaseProxy::BroadphaseProxy(Vector3 aabbMin, Vector3 aabbMax,
	IntPtr userPtr, short int collisionFilterGroup,
	short int collisionFilterMask)
{
	_proxy = new btBroadphaseProxy(
		*Math::Vector3ToBtVec3(aabbMin),
		*Math::Vector3ToBtVec3(aabbMax),
		userPtr.ToPointer(),
		collisionFilterGroup,
		collisionFilterMask
	);
}

BroadphaseProxy::BroadphaseProxy(btBroadphaseProxy* proxy)
{
	_proxy = proxy;
}

int BroadphaseProxy::Uid::get()
{
	return _proxy->getUid();
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
