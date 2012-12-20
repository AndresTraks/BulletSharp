#include "StdAfx.h"

#include "DefaultMotionState.h"

DefaultMotionState::DefaultMotionState() : BulletSharp::MotionState(new btDefaultMotionState())
{
}

DefaultMotionState::DefaultMotionState(Matrix startTrans) : BulletSharp::MotionState(new btDefaultMotionState())
{
	WorldTransform = startTrans;
}

Matrix DefaultMotionState::WorldTransform::get()
{
	btTransform* transform = ALIGNED_ALLOC(btTransform);
	_native->getWorldTransform(*transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	ALIGNED_DEL(transform);
	return m;
}
void DefaultMotionState::WorldTransform::set(Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_native->setWorldTransform(*worldTransformTemp);
	ALIGNED_DEL(worldTransformTemp);
}


void DefaultMotionState::GetWorldTransform([Out] Matrix% outTransform)
{
	btTransform* transform = ALIGNED_ALLOC(btTransform);
	_native->getWorldTransform(*transform);
	Math::BtTransformToMatrix(transform, outTransform);
	ALIGNED_DEL(transform);
}
