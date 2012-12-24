#include "StdAfx.h"

#include "MotionState.h"

MotionState::MotionState()
{
	MotionStateWrapper* state = new MotionStateWrapper();
	state->_motionState = this;
	_native = state;
}

MotionState::MotionState(btMotionState* motionState)
{
	if (motionState) {
		_native = motionState;
	}
}

MotionState::~MotionState()
{
	this->!MotionState();
}

MotionState::!MotionState()
{
	delete _native;
	_native = 0;
}
