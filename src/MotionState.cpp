#include "StdAfx.h"

#include "MotionState.h"

MotionState::MotionState(btMotionState* native)
{
	if (native) {
		_native = native;
	}
}

MotionState::MotionState()
{
	MotionStateWrapper* state = new MotionStateWrapper();
	state->_motionState = this;
	_native = state;
}

MotionState::~MotionState()
{
	this->!MotionState();
}

MotionState::!MotionState()
{
	delete _native;
	_native = NULL;
}
