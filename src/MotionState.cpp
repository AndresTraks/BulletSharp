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
	this->!MotionState();
}

MotionState::!MotionState()
{
	delete _unmanaged;
	_unmanaged = 0;
}
