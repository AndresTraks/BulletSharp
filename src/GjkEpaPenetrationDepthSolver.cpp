#include "StdAfx.h"

// Fully implemented as of 24 Nov 2010

#ifndef DISABLE_UNCOMMON

#include "GjkEpaPenetrationDepthSolver.h"

GjkEpaPenetrationDepthSolver::GjkEpaPenetrationDepthSolver()
: ConvexPenetrationDepthSolver(new btGjkEpaPenetrationDepthSolver())
{
}

#endif
