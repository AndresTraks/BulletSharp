#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ContinuousConvexCollision.h"
#include "ConvexShape.h"
#include "ConvexPenetrationDepthSolver.h"
#include "StaticPlaneShape.h"

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, ConvexShape^ shapeB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: ConvexCast(new btContinuousConvexCollision(shapeA->UnmanagedPointer, shapeB->UnmanagedPointer,
	simplexSolver->UnmanagedPointer, (penetrationDepthSolver != nullptr) ? penetrationDepthSolver->UnmanagedPointer : 0))
{
}

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, StaticPlaneShape^ shapeB)
: ConvexCast(new btContinuousConvexCollision(shapeA->UnmanagedPointer, shapeB->UnmanagedPointer))
{
}

#endif
