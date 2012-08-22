#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "GjkConvexCast.h"

GjkConvexCast::GjkConvexCast(ConvexShape^ convexA, ConvexShape^ convexB, SimplexSolverInterface^ simplexSolver)
: ConvexCast(new btGjkConvexCast((btConvexShape*)convexA->_unmanaged, (btConvexShape*)convexB->_unmanaged, simplexSolver->UnmanagedPointer))
{
}

#endif
