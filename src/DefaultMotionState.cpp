#include "StdAfx.h"

#include "DefaultMotionState.h"

DefaultMotionState::DefaultMotionState() : BulletSharp::MotionState(0)
{
#ifdef BT_USE_SSE_IN_API
	btTransform* identityMatrix = Math::MatrixToBtTransform(Matrix_Identity); // default optional parameters are not aligned
	_native = ALIGNED_NEW(btDefaultMotionState) (*identityMatrix, *identityMatrix);
	ALIGNED_FREE(identityMatrix);
#else
	_native = ALIGNED_NEW(btDefaultMotionState) ();
#endif
}

DefaultMotionState::DefaultMotionState(Matrix startTrans) : BulletSharp::MotionState(0)
{
	btTransform* startTransTemp = Math::MatrixToBtTransform(startTrans);
#ifdef BT_USE_SSE_IN_API
	btTransform* centerOfMassOffset = Math::MatrixToBtTransform(Matrix_Identity); // default optional parameters are not aligned
	_native = ALIGNED_NEW(btDefaultMotionState) (*startTransTemp, *centerOfMassOffset);
	ALIGNED_FREE(centerOfMassOffset);
#else
	_native = ALIGNED_NEW(btDefaultMotionState) (*startTransTemp);
#endif
	ALIGNED_FREE(startTransTemp);
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
