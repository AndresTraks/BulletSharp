#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "BoxBoxCollisionAlgorithm.h"
#include "BroadphaseProxy.h"
#include "ConvexPlaneCollisionAlgorithm.h"
#include "ConvexConvexAlgorithm.h"
#include "ConvexConcaveCollisionAlgorithm.h"
#include "CompoundCollisionAlgorithm.h"
#include "CompoundCompoundCollisionAlgorithm.h"
#include "EmptyCollisionAlgorithm.h"
#include "SphereSphereCollisionAlgorithm.h"
#include "SphereTriangleCollisionAlgorithm.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

CollisionConfiguration::CollisionConfiguration(btCollisionConfiguration* native)
{
	_native = native;
}

CollisionConfiguration::~CollisionConfiguration()
{
	this->!CollisionConfiguration();
}

CollisionConfiguration::!CollisionConfiguration()
{
	delete _native;
	_native = NULL;
}

CollisionAlgorithmCreateFunc^ CollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	btCollisionAlgorithmCreateFunc* createFunc = _native->getCollisionAlgorithmCreateFunc((int)proxyType0, (int)proxyType1);
	if (proxyType0 == BroadphaseNativeType::BoxShape && proxyType1 == BroadphaseNativeType::BoxShape)
	{
		return gcnew BoxBoxCollisionAlgorithm::CreateFunc(static_cast<btBoxBoxCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (proxyType0 == BroadphaseNativeType::SphereShape && proxyType1 == BroadphaseNativeType::SphereShape)
	{
		return gcnew SphereSphereCollisionAlgorithm::CreateFunc(static_cast<btSphereSphereCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (proxyType0 == BroadphaseNativeType::SphereShape && proxyType1 == BroadphaseNativeType::TriangleShape)
	{
		return gcnew SphereTriangleCollisionAlgorithm::CreateFunc(static_cast<btSphereTriangleCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (proxyType0 == BroadphaseNativeType::TriangleShape && proxyType1 == BroadphaseNativeType::SphereShape)
	{
		return gcnew SphereTriangleCollisionAlgorithm::CreateFunc(static_cast<btSphereTriangleCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (proxyType0 == BroadphaseNativeType::StaticPlaneShape && BroadphaseProxy::IsConvex(proxyType1))
	{
		return gcnew ConvexPlaneCollisionAlgorithm::CreateFunc(static_cast<btConvexPlaneCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (proxyType1 == BroadphaseNativeType::StaticPlaneShape && BroadphaseProxy::IsConvex(proxyType0))
	{
		return gcnew ConvexPlaneCollisionAlgorithm::CreateFunc(static_cast<btConvexPlaneCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	else if (BroadphaseProxy::IsConvex(proxyType0) && BroadphaseProxy::IsConvex(proxyType1))
	{
		return gcnew ConvexConvexAlgorithm::CreateFunc(static_cast<btConvexConvexAlgorithm::CreateFunc*>(createFunc));
	}
	else if (BroadphaseProxy::IsConvex(proxyType0) && BroadphaseProxy::IsConcave(proxyType1))
	{
		return gcnew ConvexConcaveCollisionAlgorithm::CreateFunc(static_cast<btConvexConcaveCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	return gcnew EmptyAlgorithm::CreateFunc(static_cast<btEmptyAlgorithm::CreateFunc*>(createFunc));
}

bool CollisionConfiguration::IsDisposed::get()
{
	return (_native == NULL);
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ CollisionConfiguration::CollisionAlgorithmPool::get()
{
	if (!_collisionAlgorithmPool)
	{
		_collisionAlgorithmPool = gcnew PoolAllocator(_native->getCollisionAlgorithmPool(), true);
	}
	return _collisionAlgorithmPool;
}

PoolAllocator^ CollisionConfiguration::PersistentManifoldPool::get()
{
	if (!_persistentManifoldPool)
	{
		_persistentManifoldPool = gcnew PoolAllocator(_native->getPersistentManifoldPool(), true);
	}
	return _persistentManifoldPool;
}
#endif
