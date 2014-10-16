#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "DefaultCollisionConfiguration.h"
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
	if (_collisionAlgorithmPool == nullptr)
	{
		_collisionAlgorithmPool = gcnew PoolAllocator(_native->m_collisionAlgorithmPool);
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

#ifndef DISABLE_UNCOMMON
PoolAllocator^ DefaultCollisionConstructionInfo::PersistentManifoldPool::get()
{
	if (_persistentManifoldPool == nullptr)
	{
		_persistentManifoldPool = gcnew PoolAllocator(_native->m_persistentManifoldPool);
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

DefaultCollisionConfiguration::DefaultCollisionConfiguration(btDefaultCollisionConfiguration* native)
	: CollisionConfiguration(native)
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
