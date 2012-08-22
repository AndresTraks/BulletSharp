#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionObjectWrapper.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"
#include "PersistentManifold.h"
#include "StackAlloc.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

DispatcherInfo::DispatcherInfo(btDispatcherInfo* info)
{
	_info = info;
}

btScalar DispatcherInfo::AllowedCcdPenetration::get()
{
	return _info->m_allowedCcdPenetration;
}
void DispatcherInfo::AllowedCcdPenetration::set(btScalar value)
{
	_info->m_allowedCcdPenetration = value;
}

btScalar DispatcherInfo::ConvexConservativeDistanceThreshold::get()
{
	return _info->m_convexConservativeDistanceThreshold;
}
void DispatcherInfo::ConvexConservativeDistanceThreshold::set(btScalar value)
{
	_info->m_convexConservativeDistanceThreshold = value;
}

#ifndef DISABLE_DEBUGDRAW
IDebugDraw^ DispatcherInfo::DebugDraw::get()
{
	return BulletSharp::DebugDraw::GetManaged(_info->m_debugDraw);
}
void DispatcherInfo::DebugDraw::set(IDebugDraw^ value)
{
	_info->m_debugDraw = BulletSharp::DebugDraw::GetUnmanaged(value);
}
#endif

DispatcherInfo::DispatchFunc DispatcherInfo::DispatchFunction::get()
{
	return (DispatcherInfo::DispatchFunc)_info->m_dispatchFunc;
}
void DispatcherInfo::DispatchFunction::set(DispatcherInfo::DispatchFunc value)
{
	_info->m_dispatchFunc = (int)value;
}

bool DispatcherInfo::EnableSatConvex::get()
{
	return _info->m_enableSatConvex;
}
void DispatcherInfo::EnableSatConvex::set(bool value)
{
	_info->m_enableSatConvex = value;
}

bool DispatcherInfo::EnableSpu::get()
{
	return _info->m_enableSPU;
}
void DispatcherInfo::EnableSpu::set(bool value)
{
	_info->m_enableSPU = value;
}

StackAlloc^ DispatcherInfo::StackAllocator::get()
{
	return gcnew StackAlloc(_info->m_stackAllocator);
}
void DispatcherInfo::StackAllocator::set(StackAlloc^ value)
{
	_info->m_stackAllocator = value->UnmanagedPointer;
}

int DispatcherInfo::StepCount::get()
{
	return _info->m_stepCount;
}
void DispatcherInfo::StepCount::set(int value)
{
	_info->m_stepCount = value;
}

btScalar DispatcherInfo::TimeOfImpact::get()
{
	return _info->m_timeOfImpact;
}
void DispatcherInfo::TimeOfImpact::set(btScalar value)
{
	_info->m_timeOfImpact = value;
}

btScalar DispatcherInfo::TimeStep::get()
{
	return _info->m_timeStep;
}
void DispatcherInfo::TimeStep::set(btScalar value)
{
	_info->m_timeStep = value;
}

bool DispatcherInfo::UseContinuous::get()
{
	return _info->m_useContinuous;
}
void DispatcherInfo::UseContinuous::set(bool value)
{
	_info->m_useContinuous = value;
}

bool DispatcherInfo::UseConvexConservativeDistanceUtil::get()
{
	return _info->m_useConvexConservativeDistanceUtil;
}
void DispatcherInfo::UseConvexConservativeDistanceUtil::set(bool value)
{
	_info->m_useConvexConservativeDistanceUtil = value;
}

bool DispatcherInfo::UseEpa::get()
{
	return _info->m_useEpa;
}
void DispatcherInfo::UseEpa::set(bool value)
{
	_info->m_useEpa = value;
}

btDispatcherInfo* DispatcherInfo::UnmanagedPointer::get()
{
	return _info;
}
void DispatcherInfo::UnmanagedPointer::set(btDispatcherInfo* info)
{
	_info = info;
}


Dispatcher::Dispatcher(btDispatcher* dispatcher)
{
	_unmanaged = dispatcher;
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

	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

IntPtr Dispatcher::AllocateCollisionAlgorithm(int size)
{
	return IntPtr(_unmanaged->allocateCollisionAlgorithm(size));
}

void Dispatcher::ClearManifold(PersistentManifold^ manifold)
{
	_unmanaged->clearManifold((btPersistentManifold*)manifold->_unmanaged);
}

void Dispatcher::DispatchAllCollisionPairs(OverlappingPairCache^ pairCache,
	DispatcherInfo^ dispatchInfo, Dispatcher^ dispatcher)
{
	_unmanaged->dispatchAllCollisionPairs(pairCache->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, dispatcher->_unmanaged);
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return gcnew CollisionAlgorithm(_unmanaged->findAlgorithm(body0Wrap->_unmanaged, body1Wrap->_unmanaged));
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	PersistentManifold^ sharedManifold)
{
	return gcnew CollisionAlgorithm(_unmanaged->findAlgorithm(
		body0Wrap->_unmanaged, body1Wrap->_unmanaged, (btPersistentManifold*)sharedManifold->_unmanaged));
}

void Dispatcher::FreeCollisionAlgorithm(IntPtr ptr)
{
	_unmanaged->freeCollisionAlgorithm(ptr.ToPointer());
}

#ifndef DISABLE_INTERNAL
PersistentManifold^ Dispatcher::GetManifoldByIndexInternal(int index)
{
	return gcnew PersistentManifold(_unmanaged->getManifoldByIndexInternal(index));
}
#endif

PersistentManifold^ Dispatcher::GetNewManifold(CollisionObject^ body0, CollisionObject^ body1)
{
	return gcnew PersistentManifold(_unmanaged->getNewManifold(
		body0->_unmanaged, body1->_unmanaged));
}

bool Dispatcher::NeedsCollision(CollisionObject^ body0, CollisionObject^ body1)
{
	return _unmanaged->needsCollision(body0->UnmanagedPointer, body1->UnmanagedPointer);
}

bool Dispatcher::NeedsResponse(CollisionObject^ body0, CollisionObject^ body1)
{
	return _unmanaged->needsResponse(body0->UnmanagedPointer, body1->UnmanagedPointer);
}

void Dispatcher::ReleaseManifold(PersistentManifold^ manifold)
{
	_unmanaged->releaseManifold((btPersistentManifold*)manifold->_unmanaged);
}

int Dispatcher::NumManifolds::get()
{
	return _unmanaged->getNumManifolds();
}

bool Dispatcher::IsDisposed::get()
{
	return (_unmanaged == NULL);
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ Dispatcher::InternalManifoldPool::get()
{
	return gcnew PoolAllocator(_unmanaged->getInternalManifoldPool());
}
#endif

btDispatcher* Dispatcher::UnmanagedPointer::get()
{
	return _unmanaged;
}
void Dispatcher::UnmanagedPointer::set(btDispatcher* value)
{
	_unmanaged = value;
}
