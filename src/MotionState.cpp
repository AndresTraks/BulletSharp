#include "StdAfx.h"

#include "DefaultMotionState.h"

using namespace BulletSharp;

MotionState::MotionState()
{
	MotionStateWrapper* state = new MotionStateWrapper();
	state->_motionState = this;
	_motionState = state;
}

MotionState::MotionState(btMotionState* motionState)
{
	_motionState = motionState;
}

MotionState::~MotionState()
{
	_motionState = 0;
}

Matrix MotionState::WorldTransform::get()
{
	btTransform* transform = new btTransform;
	_motionState->getWorldTransform(*transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	delete transform;
	return m;
}

void MotionState::WorldTransform::set(Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_motionState->setWorldTransform(*worldTransformTemp);
	delete worldTransformTemp;
}

btMotionState* MotionState::UnmanagedPointer::get()
{
	return _motionState;
}

void MotionState::UnmanagedPointer::set(btMotionState* value )
{
	_motionState = value;
}
