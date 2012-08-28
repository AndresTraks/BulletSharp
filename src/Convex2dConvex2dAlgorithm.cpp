#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "Convex2dConvex2dAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"
#include "SimplexSolverInterface.h"

Convex2dConvex2dAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver)
: CollisionAlgorithmCreateFunc(new btConvex2dConvex2dAlgorithm::CreateFunc(
	simplexSolver->UnmanagedPointer, pdSolver->_unmanaged))
{
	_simplexSolver = simplexSolver;
	_pdSolver = pdSolver;
}


Convex2dConvex2dAlgorithm::Convex2dConvex2dAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: ActivatingCollisionAlgorithm(new btConvex2dConvex2dAlgorithm((btPersistentManifold*)GetUnmanagedNullable(mf),
	*ci->_unmanaged, body0Wrap->_unmanaged, body1Wrap->_unmanaged, simplexSolver->UnmanagedPointer,
	pdSolver->_unmanaged, numPerturbationIterations, minimumPointsPerturbationThreshold))
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
#endif
