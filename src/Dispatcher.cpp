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
	_native = dispatcher;
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

void Dispatcher::DispatchAllCollisionPairs(OverlappingPairCache^ pairCache,
	DispatcherInfo^ dispatchInfo, Dispatcher^ dispatcher)
{
	_native->dispatchAllCollisionPairs(pairCache->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, dispatcher->_native);
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return gcnew CollisionAlgorithm(_native->findAlgorithm(body0Wrap->_native, body1Wrap->_native));
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	PersistentManifold^ sharedManifold)
{
	return gcnew CollisionAlgorithm(_native->findAlgorithm(
		body0Wrap->_native, body1Wrap->_native, (btPersistentManifold*)sharedManifold->_native));
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
	return _native->needsCollision(body0->UnmanagedPointer, body1->UnmanagedPointer);
}

bool Dispatcher::NeedsResponse(CollisionObject^ body0, CollisionObject^ body1)
{
	return _native->needsResponse(body0->UnmanagedPointer, body1->UnmanagedPointer);
}

void Dispatcher::ReleaseManifold(PersistentManifold^ manifold)
{
	_native->releaseManifold((btPersistentManifold*)manifold->_native);
}

int Dispatcher::NumManifolds::get()
{
	return _native->getNumManifolds();
}

bool Dispatcher::IsDisposed::get()
{
	return (_native == NULL);
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ Dispatcher::InternalManifoldPool::get()
{
	return gcnew PoolAllocator(_native->getInternalManifoldPool());
}
#endif

btDispatcher* Dispatcher::UnmanagedPointer::get()
{
	return _native;
}
void Dispatcher::UnmanagedPointer::set(btDispatcher* value)
{
	_native = value;
}
