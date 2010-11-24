#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "DefaultCollisionConfiguration.h"
#include "StackAlloc.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

DefaultCollisionConstructionInfo::DefaultCollisionConstructionInfo()
{
	_constructionInfo = new btDefaultCollisionConstructionInfo();
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::CollisionAlgorithmPool::get()
{
	return gcnew PoolAllocator(_constructionInfo->m_collisionAlgorithmPool);
}
void DefaultCollisionConstructionInfo::CollisionAlgorithmPool::set(PoolAllocator^ value)
{
	_constructionInfo->m_collisionAlgorithmPool = value->UnmanagedPointer;
}
#endif

int DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::get()
{
	return _constructionInfo->m_customCollisionAlgorithmMaxElementSize;
}
void DefaultCollisionConstructionInfo::CustomCollisionAlgorithmMaxElementSize::set(int value)
{
	_constructionInfo->m_customCollisionAlgorithmMaxElementSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::get()
{
	return _constructionInfo->m_defaultMaxCollisionAlgorithmPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxCollisionAlgorithmPoolSize::set(int value)
{
	_constructionInfo->m_defaultMaxCollisionAlgorithmPoolSize = value;
}

int DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::get()
{
	return _constructionInfo->m_defaultMaxPersistentManifoldPoolSize;
}
void DefaultCollisionConstructionInfo::DefaultMaxPersistentManifoldPoolSize::set(int value)
{
	_constructionInfo->m_defaultMaxPersistentManifoldPoolSize = value;
}

int DefaultCollisionConstructionInfo::DefaultStackAllocatorSize::get()
{
	return _constructionInfo->m_defaultStackAllocatorSize;
}
void DefaultCollisionConstructionInfo::DefaultStackAllocatorSize::set(int value)
{
	_constructionInfo->m_defaultStackAllocatorSize = value;
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::PersistentManifoldPool::get()
{
	return gcnew PoolAllocator(_constructionInfo->m_persistentManifoldPool);
}
void DefaultCollisionConstructionInfo::PersistentManifoldPool::set(PoolAllocator^ value)
{
	_constructionInfo->m_persistentManifoldPool = value->UnmanagedPointer;
}
#endif

StackAlloc^ DefaultCollisionConstructionInfo::StackAllocator::get()
{
	return gcnew StackAlloc(_constructionInfo->m_stackAlloc);
}
void DefaultCollisionConstructionInfo::StackAllocator::set(StackAlloc^ value)
{
	_constructionInfo->m_stackAlloc = value->UnmanagedPointer;
}

int DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::get()
{
	return _constructionInfo->m_useEpaPenetrationAlgorithm;
}
void DefaultCollisionConstructionInfo::UseEpaPenetrationAlgorithm::set(int value)
{
	_constructionInfo->m_useEpaPenetrationAlgorithm = value;
}

btDefaultCollisionConstructionInfo* DefaultCollisionConstructionInfo::UnmanagedPointer::get()
{
	return _constructionInfo;
}
void DefaultCollisionConstructionInfo::UnmanagedPointer::set( btDefaultCollisionConstructionInfo* value )
{
	_constructionInfo = value;
}


DefaultCollisionConfiguration::DefaultCollisionConfiguration(btDefaultCollisionConfiguration* conf)
: CollisionConfiguration(conf)
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo)
: CollisionConfiguration(new btDefaultCollisionConfiguration(*constructionInfo->UnmanagedPointer))
{
}

DefaultCollisionConfiguration::DefaultCollisionConfiguration()
: CollisionConfiguration(new btDefaultCollisionConfiguration())
{
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(
	int numPerturbationIterations)
{
	UnmanagedPointer->setConvexConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(
	int numPerturbationIterations, int minimumPointsPerturbationThreshold)
{
	UnmanagedPointer->setConvexConvexMultipointIterations(
		numPerturbationIterations, minimumPointsPerturbationThreshold);
}

btDefaultCollisionConfiguration* DefaultCollisionConfiguration::UnmanagedPointer::get()
{
	return (btDefaultCollisionConfiguration*)CollisionConfiguration::UnmanagedPointer;
}
