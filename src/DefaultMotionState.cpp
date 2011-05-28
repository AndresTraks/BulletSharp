#include "StdAfx.h"

#include "DefaultMotionState.h"

DefaultMotionState::DefaultMotionState() : BulletSharp::MotionState(new btDefaultMotionState())
{
}

DefaultMotionState::DefaultMotionState(Matrix startTrans) : BulletSharp::MotionState(new btDefaultMotionState())
{
	WorldTransform = startTrans;
}

void DefaultMotionState::GetWorldTransform([Out] Matrix% outTransform)
{
	btTransform* transform = new btTransform;
	_unmanaged->getWorldTransform(*transform);
	Math::BtTransformToMatrix(transform, outTransform);
	delete transform;
}
