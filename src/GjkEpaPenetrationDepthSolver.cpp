#include "StdAfx.h"

// Fully implemented as of 30 Jun 2010

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#pragma managed(pop)

#include "GjkEpaPenetrationDepthSolver.h"

GjkEpaPenetrationDepthSolver::GjkEpaPenetrationDepthSolver()
: ConvexPenetrationDepthSolver(new btGjkEpaPenetrationDepthSolver())
{
}
