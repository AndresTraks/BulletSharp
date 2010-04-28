#include "StdAfx.h"

#include "DiscreteCollisionDetectorInterface.h"
#include "StackAlloc.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

DiscreteCollisionDetectorInterface::ClosestPointInput::ClosestPointInput()
{
	_input = new btDiscreteCollisionDetectorInterface::ClosestPointInput;
}

Matrix DiscreteCollisionDetectorInterface::ClosestPointInput::TransformA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->m_transformA);
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::TransformA::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &UnmanagedPointer->m_transformA);
}

Matrix DiscreteCollisionDetectorInterface::ClosestPointInput::TransformB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->m_transformB);
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::TransformB::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &UnmanagedPointer->m_transformB);
}

btScalar DiscreteCollisionDetectorInterface::ClosestPointInput::MaximumDistanceSquared::get()
{
	return UnmanagedPointer->m_maximumDistanceSquared;
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::MaximumDistanceSquared::set(btScalar value)
{
	UnmanagedPointer->m_maximumDistanceSquared = value;
}

StackAlloc^ DiscreteCollisionDetectorInterface::ClosestPointInput::StackAlloc::get()
{
	if (UnmanagedPointer->m_stackAlloc == nullptr)
		return nullptr;
	return gcnew BulletSharp::StackAlloc(UnmanagedPointer->m_stackAlloc);
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::StackAlloc::set(BulletSharp::StackAlloc^ value)
{
	UnmanagedPointer->m_stackAlloc = value->UnmanagedPointer;
}

btDiscreteCollisionDetectorInterface::ClosestPointInput*
DiscreteCollisionDetectorInterface::ClosestPointInput::UnmanagedPointer::get()
{
	return _input;
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::UnmanagedPointer::set(
	btDiscreteCollisionDetectorInterface::ClosestPointInput* value)
{
	_input = value;
}

DiscreteCollisionDetectorInterface::Result::Result(
	btDiscreteCollisionDetectorInterface::Result* result)
{
	_result = result;
}

DiscreteCollisionDetectorInterface::Result::~Result()
{
	this->DiscreteCollisionDetectorInterface::Result::!Result();
}

DiscreteCollisionDetectorInterface::Result::!Result()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_result = NULL;
	
	OnDisposed( this, nullptr );
}

bool DiscreteCollisionDetectorInterface::Result::IsDisposed::get()
{
	return (_result == NULL);
}

btDiscreteCollisionDetectorInterface::Result* DiscreteCollisionDetectorInterface::Result::UnmanagedPointer::get()
{
	return _result;
}
void DiscreteCollisionDetectorInterface::Result::UnmanagedPointer::set(btDiscreteCollisionDetectorInterface::Result* value)
{
	_result = value;
}


DiscreteCollisionDetectorInterface::StorageResult::StorageResult(btStorageResult* result)
: DiscreteCollisionDetectorInterface::Result(result)
{
}


DiscreteCollisionDetectorInterface::DiscreteCollisionDetectorInterface(
	btDiscreteCollisionDetectorInterface* detectorInterface)
{
	_detectorInterface = detectorInterface;
}

DiscreteCollisionDetectorInterface::~DiscreteCollisionDetectorInterface()
{
	this->!DiscreteCollisionDetectorInterface();
}

DiscreteCollisionDetectorInterface::!DiscreteCollisionDetectorInterface()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_detectorInterface = NULL;
	
	OnDisposed( this, nullptr );
}

#ifndef DISABLE_DEBUGDRAW
void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output, DebugDraw^ debugDraw)
{
	btDiscreteCollisionDetectorInterface::Result* btResult = output->UnmanagedPointer;
	UnmanagedPointer->getClosestPoints(*input->UnmanagedPointer, *btResult,
		(debugDraw != nullptr) ? debugDraw->UnmanagedPointer : 0);
}
#else
void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output)
{
	btDiscreteCollisionDetectorInterface::Result* btResult = output->UnmanagedPointer;
	UnmanagedPointer->getClosestPoints(*input->UnmanagedPointer, *btResult, 0);
}
#endif
/*
void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output, DebugDraw^ debugDraw, bool swapResults)
{
}
*/
bool DiscreteCollisionDetectorInterface::IsDisposed::get()
{
	return (_detectorInterface == NULL);
}

btDiscreteCollisionDetectorInterface* DiscreteCollisionDetectorInterface::UnmanagedPointer::get()
{
	return _detectorInterface;
}
void DiscreteCollisionDetectorInterface::UnmanagedPointer::set(btDiscreteCollisionDetectorInterface* value)
{
	_detectorInterface = value;
}
