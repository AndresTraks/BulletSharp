#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "GjkConvexCast.h"

GjkConvexCast::GjkConvexCast(ConvexShape^ convexA, ConvexShape^ convexB, SimplexSolverInterface^ simplexSolver)
	: ConvexCast(new btGjkConvexCast((btConvexShape*)convexA->_native, (btConvexShape*)convexB->_native,
		simplexSolver->_native))
{
}

#endif
