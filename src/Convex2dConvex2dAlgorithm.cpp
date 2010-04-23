#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h>
#pragma managed(pop)

#include "CollisionObject.h"
#include "Convex2dConvex2dAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"
#include "SimplexSolverInterface.h"

Convex2dConvex2dAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver)
: CollisionAlgorithmCreateFunc(new btConvex2dConvex2dAlgorithm::CreateFunc(
	simplexSolver->UnmanagedPointer, pdSolver->UnmanagedPointer))
{
}


Convex2dConvex2dAlgorithm::Convex2dConvex2dAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ body0, CollisionObject^ body1, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: ActivatingCollisionAlgorithm(new btConvex2dConvex2dAlgorithm((mf != nullptr) ? mf->UnmanagedPointer : 0, *ci->UnmanagedPointer,
	  body0->UnmanagedPointer, body1->UnmanagedPointer, simplexSolver->UnmanagedPointer,
	pdSolver->UnmanagedPointer, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

PersistentManifold^ Convex2dConvex2dAlgorithm::Manifold::get()
{
	return gcnew PersistentManifold((btPersistentManifold*)UnmanagedPointer->getManifold());
}

btConvex2dConvex2dAlgorithm* Convex2dConvex2dAlgorithm::UnmanagedPointer::get()
{
	return (btConvex2dConvex2dAlgorithm*) CollisionAlgorithm::UnmanagedPointer;
}

#endif
