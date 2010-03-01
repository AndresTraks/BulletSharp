#include "stdafx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h>
#pragma managed(pop)

#include "MinkowskiPenetrationDepthSolver.h"

MinkowskiPenetrationDepthSolver::MinkowskiPenetrationDepthSolver()
: ConvexPenetrationDepthSolver(new btMinkowskiPenetrationDepthSolver())
{
}
