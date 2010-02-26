#include "stdafx.h"

#include "MinkowskiPenetrationDepthSolver.h"

MinkowskiPenetrationDepthSolver::MinkowskiPenetrationDepthSolver()
: ConvexPenetrationDepthSolver(new btMinkowskiPenetrationDepthSolver())
{
}
