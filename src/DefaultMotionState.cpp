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
	btTransform* transform = new btTransform;
	_unmanaged->getWorldTransform(*transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	delete transform;
	return m;
}
void DefaultMotionState::WorldTransform::set(Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_unmanaged->setWorldTransform(*worldTransformTemp);
	delete worldTransformTemp;
}


void DefaultMotionState::GetWorldTransform([Out] Matrix% outTransform)
{
	btTransform* transform = new btTransform;
	_unmanaged->getWorldTransform(*transform);
	Math::BtTransformToMatrix(transform, outTransform);
	delete transform;
}
