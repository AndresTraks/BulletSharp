#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#pragma managed(pop)

#include "ConvexPenetrationDepthSolver.h"
#include "ConvexShape.h"
#include "GjkPairDetector.h"
#include "SimplexSolverInterface.h"

GjkPairDetector::GjkPairDetector(btGjkPairDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: DiscreteCollisionDetectorInterface(new btGjkPairDetector(objectA->UnmanagedPointer,
	objectB->UnmanagedPointer, simplexSolver->UnmanagedPointer,
	(penetrationDepthSolver != nullptr) ? penetrationDepthSolver->UnmanagedPointer : 0))
{
}
