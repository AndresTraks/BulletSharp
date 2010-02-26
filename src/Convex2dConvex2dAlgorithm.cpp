#include "StdAfx.h"

#include "Convex2dConvex2dAlgorithm.h"

Convex2dConvex2dAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver)
: CollisionAlgorithmCreateFunc(new btConvex2dConvex2dAlgorithm::CreateFunc(
	simplexSolver->UnmanagedPointer, pdSolver->UnmanagedPointer))
{
}
