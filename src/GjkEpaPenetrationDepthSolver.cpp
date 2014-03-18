#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "GjkEpaPenetrationDepthSolver.h"

GjkEpaPenetrationDepthSolver::GjkEpaPenetrationDepthSolver()
	: ConvexPenetrationDepthSolver(new btGjkEpaPenetrationDepthSolver())
{
}

#endif
