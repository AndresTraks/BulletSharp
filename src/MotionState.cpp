#include "StdAfx.h"

#include "DefaultMotionState.h"

MotionState::MotionState()
{
	MotionStateWrapper* state = new MotionStateWrapper();
	state->_motionState = this;
	_unmanaged = state;
}

MotionState::MotionState(btMotionState* motionState)
{
	_unmanaged = motionState;
}

MotionState::~MotionState()
{
	_unmanaged = 0;
}

void MotionState::GetWorldTransform([Out] Matrix% outTransform)
{
	btTransform* transform = new btTransform;
	_unmanaged->getWorldTransform(*transform);
	Math::BtTransformToMatrix(transform, outTransform);
	delete transform;
}

Matrix MotionState::WorldTransform::get()
{
	btTransform* transform = new btTransform;
	_unmanaged->getWorldTransform(*transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	delete transform;
	return m;
}
void MotionState::WorldTransform::set(Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_unmanaged->setWorldTransform(*worldTransformTemp);
	delete worldTransformTemp;
}
