#include "StdAfx.h"

#include "DebugDraw.h"

DebugDraw::DebugDraw()
{
	_debugWrapper = new DebugWrapper();
	_debugWrapper->_debugDraw = this;
	_debugWrapper->setDebugMode(0);
}

void DebugDraw::SetDebugMode(DebugDrawModes debugMode)
{
	_debugWrapper->setDebugMode((int)debugMode);
}
