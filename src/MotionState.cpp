#include "StdAfx.h"

#include "MotionState.h"

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
