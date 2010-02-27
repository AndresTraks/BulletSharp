#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "DebugDraw.h"
#include "Dispatcher.h"

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

DebugDraw^ DispatcherInfo::DebugDraw::get()
{
	if (_info->m_debugDraw == nullptr)
		return nullptr;

	// Instances of btIDebugDraw can only be of type DebugWrapper.
	return gcnew BulletSharp::DebugDraw((DebugWrapper*)_info->m_debugDraw);
}
void DispatcherInfo::DebugDraw::set(BulletSharp::DebugDraw^ value)
{
	_info->m_debugDraw = value->UnmanagedPointer;
}

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

btScalar DispatcherInfo::TimeOfImpact::get()
{
	return _info->m_timeOfImpact;
}
void DispatcherInfo::TimeOfImpact::set(btScalar value)
{
	_info->m_timeOfImpact = value;
}

/*
int DispatcherInfo::StackAllocator::get()
{
	return gcnew StackAlloc(_info->m_stackAllocator);
}
void DispatcherInfo::StackAllocator::set(StackAlloc^ value)
{
	_info->m_stackAllocator = value->UnmanagedPointer;
}
*/

int DispatcherInfo::StepCount::get()
{
	return _info->m_stepCount;
}
void DispatcherInfo::StepCount::set(int value)
{
	_info->m_stepCount = value;
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
	return _info->m_convexConservativeDistanceThreshold;
}
void DispatcherInfo::UseConvexConservativeDistanceUtil::set(bool value)
{
	_info->m_convexConservativeDistanceThreshold = value;
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
	_dispatcher = dispatcher;
}

Dispatcher::~Dispatcher()
{
	this->!Dispatcher();
}

Dispatcher::!Dispatcher()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_dispatcher = NULL;
	
	OnDisposed( this, nullptr );
}

CollisionAlgorithm^ Dispatcher::FindAlgorithm(CollisionObject^ body0, CollisionObject^ body1)
{
	return gcnew CollisionAlgorithm(_dispatcher->findAlgorithm(body0->UnmanagedPointer, body1->UnmanagedPointer));
}

bool Dispatcher::NeedsCollision(CollisionObject^ body0, CollisionObject^ body1)
{
	return _dispatcher->needsCollision(body0->UnmanagedPointer, body1->UnmanagedPointer);
}

bool Dispatcher::IsDisposed::get()
{
	return (_dispatcher == NULL);
}

btDispatcher* Dispatcher::UnmanagedPointer::get()
{
	return _dispatcher;
}
void Dispatcher::UnmanagedPointer::set(btDispatcher* value)
{
	_dispatcher = value;
}
