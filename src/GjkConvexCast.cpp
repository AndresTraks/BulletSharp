#include "StdAfx.h"

#include "ConvexShape.h"
#include "GjkConvexCast.h"

GjkConvexCast::GjkConvexCast(ConvexShape^ convexA, ConvexShape^ convexB, SimplexSolverInterface^ simplexSolver)
: ConvexCast(new btGjkConvexCast(convexA->UnmanagedPointer, convexB->UnmanagedPointer, simplexSolver->UnmanagedPointer))
{
}
