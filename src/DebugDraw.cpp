#include "StdAfx.h"

#include "DebugDraw.h"

DebugDraw::DebugDraw()
{
	_debugWrapper = new DebugWrapper();
	_debugWrapper->_debugDraw = this;
	_debugWrapper->setDebugMode(0);
}

DebugDraw::DebugDraw(DebugWrapper* debugDraw)
{
	_debugWrapper = debugDraw;
}

void DebugDraw::SetDebugMode(DebugDrawModes debugMode)
{
	_debugWrapper->setDebugMode((int)debugMode);
}

DebugWrapper* DebugDraw::UnmanagedPointer::get()
{
	return _debugWrapper;
}

void DebugDraw::UnmanagedPointer::set(DebugWrapper* value)
{
	_debugWrapper = value;
}
