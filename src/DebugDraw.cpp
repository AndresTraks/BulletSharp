#include "StdAfx.h"

#ifndef DISABLE_DEBUGDRAW

#include "DebugDraw.h"

DebugDraw::DebugDraw()
{
	_debugDraw = new DebugWrapper();
	_debugDraw->_debugDraw = this;
	_debugDraw->setDebugMode(0);
}

DebugDraw::DebugDraw(DebugWrapper* debugDraw)
{
	_debugDraw = debugDraw;
}

void DebugDraw::SetDebugMode(DebugDrawModes debugMode)
{
	_debugDraw->setDebugMode((int)debugMode);
}

DebugWrapper* DebugDraw::UnmanagedPointer::get()
{
	return _debugDraw;
}

void DebugDraw::UnmanagedPointer::set(DebugWrapper* value)
{
	_debugDraw = value;
}

#endif
