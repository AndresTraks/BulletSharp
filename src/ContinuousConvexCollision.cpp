#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ContinuousConvexCollision.h"
#include "ConvexShape.h"
#include "ConvexPenetrationDepthSolver.h"
#include "StaticPlaneShape.h"

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, ConvexShape^ shapeB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: ConvexCast(new btContinuousConvexCollision((btConvexShape*)shapeA->_native, (btConvexShape*)shapeB->_native,
	simplexSolver->_native, GetUnmanagedNullable(penetrationDepthSolver)))
{
}

ContinuousConvexCollision::ContinuousConvexCollision(ConvexShape^ shapeA, StaticPlaneShape^ shapeB)
: ConvexCast(new btContinuousConvexCollision((btConvexShape*)shapeA->_native, (btStaticPlaneShape*)shapeB->_native))
{
}

#endif
