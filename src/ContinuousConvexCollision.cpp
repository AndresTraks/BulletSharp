#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ContinuousConvexCollision.h"
#include "ConvexShape.h"
#include "ConvexPenetrationDepthSolver.h"
#include "StaticPlaneShape.h"

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, ConvexShape^ shapeB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: ConvexCast(new btContinuousConvexCollision((btConvexShape*)shapeA->_unmanaged, (btConvexShape*)shapeB->_unmanaged,
	simplexSolver->UnmanagedPointer, GetUnmanagedNullable(penetrationDepthSolver)))
{
}

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, StaticPlaneShape^ shapeB)
: ConvexCast(new btContinuousConvexCollision((btConvexShape*)shapeA->_unmanaged, (btStaticPlaneShape*)shapeB->_unmanaged))
{
}

#endif
