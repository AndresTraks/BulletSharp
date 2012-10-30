#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "DefaultCollisionConfiguration.h"
#include "StackAlloc.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

DefaultCollisionConstructionInfo::DefaultCollisionConstructionInfo()
{
	_native = new btDefaultCollisionConstructionInfo();
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::CollisionAlgorithmPool::get()
{
	return gcnew PoolAllocator(_native->m_collisionAlgorithmPool);
}
void DefaultCollisionConstructionInfo::CollisionAlgorithmPool::set(PoolAllocator^ value)
{
	_native->m_collisionAlgorithmPool = value->UnmanagedPointer;
}
#endif

int DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::get()
{
	return _native->m_customCollisionAlgorithmMaxElementSize;
}
void DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::set(int value)
{
	_native->m_customCollisionAlgorithmMaxElementSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::get()
{
	return _native->m_defaultMaxCollisionAlgorithmPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::set(int value)
{
	_native->m_defaultMaxCollisionAlgorithmPoolSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::get()
{
	return _native->m_defaultMaxPersistentManifoldPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::set(int value)
{
	_native->m_defaultMaxPersistentManifoldPoolSize = value;
}

int DefaultCollisionConstructionInfo::DefaultStackAllocatorSize::get()
{
	return _native->m_defaultStackAllocatorSize;
}
void DefaultCollisionConstructionInfo::DefaultStackAllocatorSize::set(int value)
{
	_native->m_defaultStackAllocatorSize = value;
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::PersistentManifoldPool::get()
{
	return gcnew PoolAllocator(_native->m_persistentManifoldPool);
}
void DefaultCollisionConstructionInfo::PersistentManifoldPool::set(PoolAllocator^ value)
{
	_native->m_persistentManifoldPool = value->UnmanagedPointer;
}
#endif

StackAlloc^ DefaultCollisionConstructionInfo::StackAllocator::get()
{
	return gcnew StackAlloc(_native->m_stackAlloc);
}
void DefaultCollisionConstructionInfo::StackAllocator::set(StackAlloc^ value)
{
	_native->m_stackAlloc = value->UnmanagedPointer;
}

int DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::get()
{
	return _native->m_useEpaPenetrationAlgorithm;
}
void DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::set(int value)
{
	_native->m_useEpaPenetrationAlgorithm = value;
}


#define Native static_cast<btDefaultCollisionConfiguration*>(_native)

DefaultCollisionConfiguration::DefaultCollisionConfiguration(btDefaultCollisionConfiguration* conf)
: CollisionConfiguration(conf)
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo)
: CollisionConfiguration(new btDefaultCollisionConfiguration(*constructionInfo->_native))
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration()
: CollisionConfiguration(new btDefaultCollisionConfiguration())
{
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations()
{
	Native->setConvexConvexMultipointIterations();
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(int numPerturbationIterations)
{
	Native->setConvexConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(
	int numPerturbationIterations, int minimumPointsPerturbationThreshold)
{
	Native->setConvexConvexMultipointIterations(
		numPerturbationIterations, minimumPointsPerturbationThreshold);
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations()
{
	Native->setPlaneConvexMultipointIterations();
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations(int numPerturbationIterations)
{
	Native->setPlaneConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetPlaneConvexMultipointIterations(
	int numPerturbationIterations, int minimumPointsPerturbationThreshold)
{
	Native->setPlaneConvexMultipointIterations(
		numPerturbationIterations, minimumPointsPerturbationThreshold);
}
