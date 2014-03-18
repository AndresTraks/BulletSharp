#include "StdAfx.h"

#include "DiscreteCollisionDetectorInterface.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

DiscreteCollisionDetectorInterface::ClosestPointInput::ClosestPointInput()
{
	_native = ALIGNED_NEW(btDiscreteCollisionDetectorInterface::ClosestPointInput) ();
}

DiscreteCollisionDetectorInterface::ClosestPointInput::~ClosestPointInput()
{
	this->!ClosestPointInput();
}

DiscreteCollisionDetectorInterface::ClosestPointInput::!ClosestPointInput()
{
	ALIGNED_FREE(_native);
	_native = NULL;
}

btScalar DiscreteCollisionDetectorInterface::ClosestPointInput::MaximumDistanceSquared::get()
{
	return _native->m_maximumDistanceSquared;
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::MaximumDistanceSquared::set(btScalar value)
{
	_native->m_maximumDistanceSquared = value;
}

Matrix DiscreteCollisionDetectorInterface::ClosestPointInput::TransformA::get()
{
	return Math::BtTransformToMatrix(&_native->m_transformA);
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::TransformA::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_transformA);
}

Matrix DiscreteCollisionDetectorInterface::ClosestPointInput::TransformB::get()
{
	return Math::BtTransformToMatrix(&_native->m_transformB);
}
void DiscreteCollisionDetectorInterface::ClosestPointInput::TransformB::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_transformB);
}


DiscreteCollisionDetectorInterface::Result::Result(
	btDiscreteCollisionDetectorInterface::Result* result)
{
	_native = result;
}

DiscreteCollisionDetectorInterface::Result::~Result()
{
	this->DiscreteCollisionDetectorInterface::Result::!Result();
}

DiscreteCollisionDetectorInterface::Result::!Result()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	ALIGNED_FREE(_native);
	_native = NULL;

	OnDisposed(this, nullptr);
}

bool DiscreteCollisionDetectorInterface::Result::IsDisposed::get()
{
	return (_native == NULL);
}


DiscreteCollisionDetectorInterface::DiscreteCollisionDetectorInterface(
	btDiscreteCollisionDetectorInterface* detectorInterface)
{
	_native = detectorInterface;
}

DiscreteCollisionDetectorInterface::~DiscreteCollisionDetectorInterface()
{
	this->!DiscreteCollisionDetectorInterface();
}

DiscreteCollisionDetectorInterface::!DiscreteCollisionDetectorInterface()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	ALIGNED_FREE(_native);
	_native = NULL;

	OnDisposed(this, nullptr);
}

#ifndef DISABLE_DEBUGDRAW
void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw)
{
	_native->getClosestPoints(*input->_native, *output->_native,
		DebugDraw::GetUnmanaged(debugDraw));
}

void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw, bool swapResults)
{
	_native->getClosestPoints(*input->_native, *output->_native,
		DebugDraw::GetUnmanaged(debugDraw), swapResults);
}
#else
void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output)
{
	_native->getClosestPoints(*input->_native, *output->_native, 0);
}

void DiscreteCollisionDetectorInterface::GetClosestPoints(
	ClosestPointInput^ input, Result^ output, bool swapResults)
{
	_native->getClosestPoints(*input->_native, *output->_native, 0, swapResults);
}
#endif

bool DiscreteCollisionDetectorInterface::IsDisposed::get()
{
	return (_native == NULL);
}


#define Native static_cast<btStorageResultWrapper*>(_native)

StorageResult::StorageResult(btStorageResultWrapper* result)
: DiscreteCollisionDetectorInterface::Result(result)
{
}

StorageResult::StorageResult()
	: DiscreteCollisionDetectorInterface::Result(0)
{
	_native = ALIGNED_NEW(btStorageResultWrapper)(this);
}

void StorageResult::AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth)
{
	VECTOR3_DEF(normalOnBInWorld);
	VECTOR3_DEF(pointInWorld);
	Native->addContactPoint(VECTOR3_USE(normalOnBInWorld), VECTOR3_USE(pointInWorld), depth);
	VECTOR3_DEL(normalOnBInWorld);
	VECTOR3_DEL(pointInWorld);
}

Vector3 StorageResult::ClosestPointInB::get()
{
	return Math::BtVector3ToVector3(&Native->m_closestPointInB);
}
void StorageResult::ClosestPointInB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_closestPointInB);
}

btScalar StorageResult::Distance::get()
{
	return Native->m_distance;
}
void StorageResult::Distance::set(btScalar value)
{
	Native->m_distance = value;
}

Vector3 StorageResult::NormalOnSurfaceB::get()
{
	return Math::BtVector3ToVector3(&Native->m_normalOnSurfaceB);
}
void StorageResult::NormalOnSurfaceB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_normalOnSurfaceB);
}


btStorageResultWrapper::btStorageResultWrapper(gcroot<StorageResult^> storageResult)
{
	_storageResult = storageResult;
}

void btStorageResultWrapper::setShapeIdentifiersA(int partId0, int index0)
{
	_storageResult->SetShapeIdentifiersA(partId0, index0);
}

void btStorageResultWrapper::setShapeIdentifiersB(int partId1, int index1)
{
	_storageResult->SetShapeIdentifiersB(partId1, index1);
}
