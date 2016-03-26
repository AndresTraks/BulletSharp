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
#include "DefaultCollisionConfiguration.h"
#include "EmptyCollisionAlgorithm.h"
#include "SphereSphereCollisionAlgorithm.h"
#include "SphereTriangleCollisionAlgorithm.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#include "VoronoiSimplexSolver.h"
#endif

DefaultCollisionConstructionInfo::~DefaultCollisionConstructionInfo()
{
	this->!DefaultCollisionConstructionInfo();
}

DefaultCollisionConstructionInfo::!DefaultCollisionConstructionInfo()
{
	delete _native;
	_native = NULL;
}

DefaultCollisionConstructionInfo::DefaultCollisionConstructionInfo()
{
	_native = new btDefaultCollisionConstructionInfo();
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::CollisionAlgorithmPool::get()
{
	if (!_collisionAlgorithmPool && _native->m_collisionAlgorithmPool)
	{
		_collisionAlgorithmPool = gcnew PoolAllocator(_native->m_collisionAlgorithmPool, true);
	}
	return _collisionAlgorithmPool;
}
void DefaultCollisionConstructionInfo::CollisionAlgorithmPool::set(PoolAllocator^ value)
{
	_native->m_collisionAlgorithmPool = value->_native;
	_collisionAlgorithmPool = value;
}
#endif

int DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::get()
{
	return _native->m_customCollisionAlgorithmMaxElementSize;
}
void DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::set(
	int value)
{
	_native->m_customCollisionAlgorithmMaxElementSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::get()
{
	return _native->m_defaultMaxCollisionAlgorithmPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::set(
	int value)
{
	_native->m_defaultMaxCollisionAlgorithmPoolSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::get()
{
	return _native->m_defaultMaxPersistentManifoldPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::set(
	int value)
{
	_native->m_defaultMaxPersistentManifoldPoolSize = value;
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::PersistentManifoldPool::get()
{
	if (!_persistentManifoldPool && _native->m_persistentManifoldPool)
	{
		_persistentManifoldPool = gcnew PoolAllocator(_native->m_persistentManifoldPool, true);
	}
	return _persistentManifoldPool;
}
void DefaultCollisionConstructionInfo::PersistentManifoldPool::set(PoolAllocator^ value)
{
	_native->m_persistentManifoldPool = value->_native;
	_persistentManifoldPool = value;
}
#endif

int DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::get()
{
	return _native->m_useEpaPenetrationAlgorithm;
}
void DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::set(int value)
{
	_native->m_useEpaPenetrationAlgorithm = value;
}


#define Native static_cast<btDefaultCollisionConfiguration*>(_native)

DefaultCollisionConfiguration::DefaultCollisionConfiguration(btDefaultCollisionConfiguration* native,
	PoolAllocator^ collisionAlgorithmPool, PoolAllocator^ persistentManifoldPool)
	: CollisionConfiguration(native, collisionAlgorithmPool, persistentManifoldPool)
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo)
	: CollisionConfiguration(new btDefaultCollisionConfiguration(*constructionInfo->_native),
		constructionInfo->CollisionAlgorithmPool, constructionInfo->PersistentManifoldPool)
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration()
	: CollisionConfiguration(new btDefaultCollisionConfiguration(), nullptr, nullptr)
{
}

CollisionAlgorithmCreateFunc^ DefaultCollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	btCollisionAlgorithmCreateFunc* createFunc = _native->getCollisionAlgorithmCreateFunc((int)proxyType0, (int)proxyType1);
	if (proxyType0 == BroadphaseNativeType::BoxShape && proxyType1 == BroadphaseNativeType::BoxShape)
	{
		return gcnew BoxBoxCollisionAlgorithm::CreateFunc(static_cast<btBoxBoxCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (proxyType0 == BroadphaseNativeType::SphereShape && proxyType1 == BroadphaseNativeType::SphereShape)
	{
		return gcnew SphereSphereCollisionAlgorithm::CreateFunc(static_cast<btSphereSphereCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (proxyType0 == BroadphaseNativeType::SphereShape && proxyType1 == BroadphaseNativeType::TriangleShape)
	{
		return gcnew SphereTriangleCollisionAlgorithm::CreateFunc(static_cast<btSphereTriangleCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (proxyType0 == BroadphaseNativeType::TriangleShape && proxyType1 == BroadphaseNativeType::SphereShape)
	{
		return gcnew SphereTriangleCollisionAlgorithm::CreateFunc(static_cast<btSphereTriangleCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (proxyType0 == BroadphaseNativeType::StaticPlaneShape && BroadphaseProxy::IsConvex(proxyType1))
	{
		return gcnew ConvexPlaneCollisionAlgorithm::CreateFunc(static_cast<btConvexPlaneCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (proxyType1 == BroadphaseNativeType::StaticPlaneShape && BroadphaseProxy::IsConvex(proxyType0))
	{
		return gcnew ConvexPlaneCollisionAlgorithm::CreateFunc(static_cast<btConvexPlaneCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (BroadphaseProxy::IsConvex(proxyType0) && BroadphaseProxy::IsConvex(proxyType1))
	{
		return gcnew ConvexConvexAlgorithm::CreateFunc(static_cast<btConvexConvexAlgorithm::CreateFunc*>(createFunc));
	}
	if (BroadphaseProxy::IsConvex(proxyType0) && BroadphaseProxy::IsConcave(proxyType1))
	{
		return gcnew ConvexConcaveCollisionAlgorithm::CreateFunc(static_cast<btConvexConcaveCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (BroadphaseProxy::IsConvex(proxyType1) && BroadphaseProxy::IsConcave(proxyType0))
	{
		return gcnew ConvexConcaveCollisionAlgorithm::SwappedCreateFunc(static_cast<btConvexConcaveCollisionAlgorithm::SwappedCreateFunc*>(createFunc));
	}
	if (BroadphaseProxy::IsCompound(proxyType0))
	{
		return gcnew CompoundCompoundCollisionAlgorithm::CreateFunc(static_cast<btCompoundCompoundCollisionAlgorithm::CreateFunc*>(createFunc));
	}
	if (BroadphaseProxy::IsCompound(proxyType1))
	{
		return gcnew CompoundCompoundCollisionAlgorithm::SwappedCreateFunc(static_cast<btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc*>(createFunc));
	}
	return gcnew EmptyAlgorithm::CreateFunc(static_cast<btEmptyAlgorithm::CreateFunc*>(createFunc));
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(int numPerturbationIterations,
	int minimumPointsPerturbationThreshold)
{
	Native->setConvexConvexMultipointIterations(numPerturbationIterations, minimumPointsPerturbationThreshold);
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(int numPerturbationIterations)
{
	Native->setConvexConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations()
{
	Native->setConvexConvexMultipointIterations();
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations(int numPerturbationIterations,
	int minimumPointsPerturbationThreshold)
{
	Native->setPlaneConvexMultipointIterations(numPerturbationIterations, minimumPointsPerturbationThreshold);
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations(int numPerturbationIterations)
{
	Native->setPlaneConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations()
{
	Native->setPlaneConvexMultipointIterations();
}
#ifndef DISABLE_UNCOMMON
VoronoiSimplexSolver^ DefaultCollisionConfiguration::SimplexSolver::get()
{
	if (_simplexSolver == nullptr) {
		_simplexSolver = gcnew VoronoiSimplexSolver(Native->getSimplexSolver(), true);
	}
	return _simplexSolver;
}
#endif
