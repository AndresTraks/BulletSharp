#include "StdAfx.h"

#include "ContinuousConvexCollision.h"
#include "ConvexShape.h"
#include "ConvexPenetrationDepthSolver.h"

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ convexA, ConvexShape^ convexB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: ConvexCast(new btContinuousConvexCollision(convexA->UnmanagedPointer, convexB->UnmanagedPointer,
	simplexSolver->UnmanagedPointer, (penetrationDepthSolver != nullptr) ? penetrationDepthSolver->UnmanagedPointer : 0))
{
}
