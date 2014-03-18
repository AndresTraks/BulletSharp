#include "StdAfx.h"

#include "DefaultMotionState.h"

#define Native static_cast<btDefaultMotionState*>(_native)

DefaultMotionState::DefaultMotionState(Matrix startTrans, Matrix centerOfMassOffset)
	: MotionState(0)
{
	TRANSFORM_CONV(startTrans);
	TRANSFORM_CONV(centerOfMassOffset);
	_native = ALIGNED_NEW(btDefaultMotionState) (TRANSFORM_USE(startTrans), TRANSFORM_USE(centerOfMassOffset));
	TRANSFORM_DEL(startTrans);
	TRANSFORM_DEL(centerOfMassOffset);
}

DefaultMotionState::DefaultMotionState(Matrix startTrans)
	: MotionState(0)
{
	TRANSFORM_CONV(startTrans);
#ifdef BT_USE_SSE_IN_API
	btTransform* centerOfMassOffset = Math::MatrixToBtTransform(Matrix_Identity); // default optional parameters are not aligned
	_native = ALIGNED_NEW(btDefaultMotionState) (TRANSFORM_USE(startTrans), *centerOfMassOffset);
	ALIGNED_FREE(centerOfMassOffset);
#else
	_native = ALIGNED_NEW(btDefaultMotionState) (TRANSFORM_USE(startTrans));
#endif
	TRANSFORM_DEL(startTrans);
}

DefaultMotionState::DefaultMotionState()
	: MotionState(0)
{
#ifdef BT_USE_SSE_IN_API
	btTransform* identityMatrix = Math::MatrixToBtTransform(Matrix_Identity); // default optional parameters are not aligned
	_native = ALIGNED_NEW(btDefaultMotionState) (*identityMatrix, *identityMatrix);
	ALIGNED_FREE(identityMatrix);
#else
	_native = ALIGNED_NEW(btDefaultMotionState) ();
#endif
}

Matrix DefaultMotionState::CenterOfMassOffset::get()
{
	return Math::BtTransformToMatrix(&Native->m_centerOfMassOffset);
}
void DefaultMotionState::CenterOfMassOffset::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &Native->m_centerOfMassOffset);
}

Matrix DefaultMotionState::GraphicsWorldTrans::get()
{
	return Math::BtTransformToMatrix(&Native->m_graphicsWorldTrans);
}
void DefaultMotionState::GraphicsWorldTrans::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &Native->m_graphicsWorldTrans);
}

Matrix DefaultMotionState::StartWorldTrans::get()
{
	return Math::BtTransformToMatrix(&Native->m_startWorldTrans);
}
void DefaultMotionState::StartWorldTrans::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &Native->m_startWorldTrans);
}

Object^ DefaultMotionState::UserObject::get()
{
	return _userObject;
}
void DefaultMotionState::UserObject::set(Object^ value)
{
	_userObject = value;
}

Matrix DefaultMotionState::WorldTransform::get()
{
	btTransform* transform = ALIGNED_NEW(btTransform);
	_native->getWorldTransform(*transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	ALIGNED_FREE(transform);
	return m;
}
void DefaultMotionState::WorldTransform::set(Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_native->setWorldTransform(*worldTransformTemp);
	ALIGNED_FREE(worldTransformTemp);
}


void DefaultMotionState::GetWorldTransform([Out] Matrix% outTransform)
{
	btTransform* transform = ALIGNED_NEW(btTransform);
	_native->getWorldTransform(*transform);
	Math::BtTransformToMatrix(transform, outTransform);
	ALIGNED_FREE(transform);
}
