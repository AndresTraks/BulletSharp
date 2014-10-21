#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "MinkowskiPenetrationDepthSolver.h"

MinkowskiPenetrationDepthSolver::MinkowskiPenetrationDepthSolver()
	: ConvexPenetrationDepthSolver(new btMinkowskiPenetrationDepthSolver())
{
}

#endif
