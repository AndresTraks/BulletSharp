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
	if (_debugDrawWrapper) {
		if (_debugDrawWrapper == _native->m_debugDraw) {
			return _debugDraw;
		} else {
			delete _debugDrawWrapper;
			_debugDrawWrapper = 0;
		}
	}

	if (_native->m_debugDraw) {
		DebugDrawWrapper* wrapper = dynamic_cast<DebugDrawWrapper*>(_native->m_debugDraw);
		DebugDraw = static_cast<IDebugDraw^>(wrapper->_debugDraw.Target);
		return _debugDraw;
	}

	return nullptr;
}
void DispatcherInfo::DebugDraw::set(IDebugDraw^ value)
{
	if (_debugDrawWrapper) {
		if (_debugDrawWrapper == _native->m_debugDraw && _debugDrawWrapper->_debugDraw.Target == value) {
			return;
		}

		// Clear IDebugDraw wrapper
		delete _debugDrawWrapper;
		_debugDrawWrapper = 0;
	}

	_debugDraw = value;
	if (!value) {
		_debugDrawWrapper = 0;
		_native->m_debugDraw = 0;
		return;
	}

	BulletSharp::DebugDraw^ cast = dynamic_cast<BulletSharp::DebugDraw^>(value);
	if (cast) {
		_debugDrawWrapper = 0;
		_native->m_debugDraw = cast->_native;
	} else {
		// Create IDebugDraw wrapper, remember to delete it
		_debugDrawWrapper = new DebugDrawWrapper(value, false);
		_native->m_debugDraw = _debugDrawWrapper;
	}
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
	_dispatcherInfoRefs = gcnew Dictionary<IntPtr, DispatcherInfo^>();
}

Dispatcher::~Dispatcher()
{
	this->!Dispatcher();
}

Dispatcher::!Dispatcher()
{
	delete _native;
	_native = NULL;
}

IntPtr Dispatcher::AllocateCollisionAlgorithm(int size)
{
	return IntPtr(_native->allocateCollisionAlgorithm(size));
}

void Dispatcher::ClearManifold(PersistentManifold manifold)
{
	_native->clearManifold(manifold._native);
}

void Dispatcher::DispatchAllCollisionPairs(OverlappingPairCache^ pairCache, DispatcherInfo^ dispatchInfo,
	Dispatcher^ dispatcher)
{
	_native->dispatchAllCollisionPairs((btOverlappingPairCache*)pairCache->_native,
		*dispatchInfo->_native, dispatcher->_native);
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	PersistentManifold sharedManifold)
{
	return CollisionAlgorithm::GetManaged(_native->findAlgorithm(
		body0Wrap->_native, body1Wrap->_native, sharedManifold._native));
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return CollisionAlgorithm::GetManaged(_native->findAlgorithm(body0Wrap->_native, body1Wrap->_native));
}

void Dispatcher::FreeCollisionAlgorithm(IntPtr ptr)
{
	_native->freeCollisionAlgorithm(ptr.ToPointer());
}

#ifndef DISABLE_INTERNAL
PersistentManifold Dispatcher::GetManifoldByIndexInternal(int index)
{
	return PersistentManifold(_native->getManifoldByIndexInternal(index));
}
#endif

PersistentManifold Dispatcher::GetNewManifold(CollisionObject^ body0, CollisionObject^ body1)
{
	return PersistentManifold(_native->getNewManifold(
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

void Dispatcher::ReleaseManifold(PersistentManifold manifold)
{
	_native->releaseManifold(manifold._native);
}
/*
PersistentManifold Dispatcher::InternalManifoldPointer::get()
{
	return _native->getInternalManifoldPointer();
}
*/
#ifndef DISABLE_UNCOMMON
PoolAllocator^ Dispatcher::InternalManifoldPool::get()
{
	if (!_internalManifoldPool)
	{
		_internalManifoldPool = gcnew PoolAllocator(_native->getInternalManifoldPool(), true);
	}
	return _internalManifoldPool;
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
