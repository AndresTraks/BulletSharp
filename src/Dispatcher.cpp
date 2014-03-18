#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionObjectWrapper.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "PersistentManifold.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

DispatcherInfo::DispatcherInfo(btDispatcherInfo* native)
{
	_native = native;
}

btScalar DispatcherInfo::AllowedCcdPenetration::get()
{
	return _native->m_allowedCcdPenetration;
}
void DispatcherInfo::AllowedCcdPenetration::set(btScalar value)
{
	_native->m_allowedCcdPenetration = value;
}

btScalar DispatcherInfo::ConvexConservativeDistanceThreshold::get()
{
	return _native->m_convexConservativeDistanceThreshold;
}
void DispatcherInfo::ConvexConservativeDistanceThreshold::set(btScalar value)
{
	_native->m_convexConservativeDistanceThreshold = value;
}

#ifndef DISABLE_DEBUGDRAW
IDebugDraw^ DispatcherInfo::DebugDraw::get()
{
	return BulletSharp::DebugDraw::GetManaged(_native->m_debugDraw);
}
void DispatcherInfo::DebugDraw::set(IDebugDraw^ value)
{
	_native->m_debugDraw = BulletSharp::DebugDraw::GetUnmanaged(value);
}
#endif

DispatcherInfo::DispatchFunc DispatcherInfo::DispatchFunction::get()
{
	return (DispatcherInfo::DispatchFunc)_native->m_dispatchFunc;
}
void DispatcherInfo::DispatchFunction::set(DispatcherInfo::DispatchFunc value)
{
	_native->m_dispatchFunc = (int)value;
}

bool DispatcherInfo::EnableSatConvex::get()
{
	return _native->m_enableSatConvex;
}
void DispatcherInfo::EnableSatConvex::set(bool value)
{
	_native->m_enableSatConvex = value;
}

bool DispatcherInfo::EnableSpu::get()
{
	return _native->m_enableSPU;
}
void DispatcherInfo::EnableSpu::set(bool value)
{
	_native->m_enableSPU = value;
}

int DispatcherInfo::StepCount::get()
{
	return _native->m_stepCount;
}
void DispatcherInfo::StepCount::set(int value)
{
	_native->m_stepCount = value;
}

btScalar DispatcherInfo::TimeOfImpact::get()
{
	return _native->m_timeOfImpact;
}
void DispatcherInfo::TimeOfImpact::set(btScalar value)
{
	_native->m_timeOfImpact = value;
}

btScalar DispatcherInfo::TimeStep::get()
{
	return _native->m_timeStep;
}
void DispatcherInfo::TimeStep::set(btScalar value)
{
	_native->m_timeStep = value;
}

bool DispatcherInfo::UseContinuous::get()
{
	return _native->m_useContinuous;
}
void DispatcherInfo::UseContinuous::set(bool value)
{
	_native->m_useContinuous = value;
}

bool DispatcherInfo::UseConvexConservativeDistanceUtil::get()
{
	return _native->m_useConvexConservativeDistanceUtil;
}
void DispatcherInfo::UseConvexConservativeDistanceUtil::set(bool value)
{
	_native->m_useConvexConservativeDistanceUtil = value;
}

bool DispatcherInfo::UseEpa::get()
{
	return _native->m_useEpa;
}
void DispatcherInfo::UseEpa::set(bool value)
{
	_native->m_useEpa = value;
}


Dispatcher::Dispatcher(btDispatcher* native)
{
	_native = native;
}

Dispatcher::~Dispatcher()
{
	this->!Dispatcher();
}

Dispatcher::!Dispatcher()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

IntPtr Dispatcher::AllocateCollisionAlgorithm(int size)
{
	return IntPtr(_native->allocateCollisionAlgorithm(size));
}

void Dispatcher::ClearManifold(PersistentManifold^ manifold)
{
	_native->clearManifold((btPersistentManifold*)manifold->_native);
}

void Dispatcher::DispatchAllCollisionPairs(OverlappingPairCache^ pairCache, DispatcherInfo^ dispatchInfo,
	Dispatcher^ dispatcher)
{
	_native->dispatchAllCollisionPairs((btOverlappingPairCache*)pairCache->_native, *dispatchInfo->_native,
		dispatcher->_native);
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	PersistentManifold^ sharedManifold)
{
	return gcnew CollisionAlgorithm(_native->findAlgorithm(
		body0Wrap->_native, body1Wrap->_native, (btPersistentManifold*)sharedManifold->_native));
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return gcnew CollisionAlgorithm(_native->findAlgorithm(body0Wrap->_native, body1Wrap->_native));
}

void Dispatcher::FreeCollisionAlgorithm(IntPtr ptr)
{
	_native->freeCollisionAlgorithm(ptr.ToPointer());
}

#ifndef DISABLE_INTERNAL
PersistentManifold^ Dispatcher::GetManifoldByIndexInternal(int index)
{
	return gcnew PersistentManifold(_native->getManifoldByIndexInternal(index));
}
#endif

PersistentManifold^ Dispatcher::GetNewManifold(CollisionObject^ body0, CollisionObject^ body1)
{
	return gcnew PersistentManifold(_native->getNewManifold(
		body0->_native, body1->_native));
}

bool Dispatcher::NeedsCollision(CollisionObject^ body0, CollisionObject^ body1)
{
	return _native->needsCollision(body0->_native, body1->_native);
}

bool Dispatcher::NeedsResponse(CollisionObject^ body0, CollisionObject^ body1)
{
	return _native->needsResponse(body0->_native, body1->_native);
}

void Dispatcher::ReleaseManifold(PersistentManifold^ manifold)
{
	_native->releaseManifold((btPersistentManifold*)manifold->_native);
}
/*
PersistentManifold^ Dispatcher::InternalManifoldPointer::get()
{
	return _native->getInternalManifoldPointer();
}
*/
#ifndef DISABLE_UNCOMMON
PoolAllocator^ Dispatcher::InternalManifoldPool::get()
{
	return gcnew PoolAllocator(_native->getInternalManifoldPool());
}
#endif

bool Dispatcher::IsDisposed::get()
{
	return (_native == NULL);
}

int Dispatcher::NumManifolds::get()
{
	return _native->getNumManifolds();
}

