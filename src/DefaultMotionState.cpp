#include "StdAfx.h"

#include "DefaultMotionState.h"

DefaultMotionState::DefaultMotionState() : BulletSharp::MotionState(new btDefaultMotionState())
{
}

DefaultMotionState::DefaultMotionState(Matrix startTrans) : BulletSharp::MotionState(new btDefaultMotionState())
{
	WorldTransform = startTrans;
}
