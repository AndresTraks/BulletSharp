#include "StdAfx.h"

#include "DefaultMotionState.h"

using namespace BulletSharp;

DefaultMotionState::DefaultMotionState() : BulletSharp::MotionState(new btDefaultMotionState())
{
}

DefaultMotionState::DefaultMotionState(Matrix startTrans) : BulletSharp::MotionState(new btDefaultMotionState())
{
	WorldTransform = startTrans;
}

btDefaultMotionState* DefaultMotionState::UnmanagedPointer::get()
{
	return (btDefaultMotionState*)MotionState::UnmanagedPointer;
}
