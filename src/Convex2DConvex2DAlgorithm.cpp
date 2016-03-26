#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "Convex2DConvex2DAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"
#include "SimplexSolverInterface.h"

#define Native static_cast<btConvex2dConvex2dAlgorithm::CreateFunc*>(_native)

Convex2DConvex2DAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver)
	: CollisionAlgorithmCreateFunc(new btConvex2dConvex2dAlgorithm::CreateFunc(simplexSolver->_native,
		pdSolver->_native), false)
{
	_pdSolver = pdSolver;
	_simplexSolver = simplexSolver;
}

int Convex2DConvex2DAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::get()
{
	return Native->m_minimumPointsPerturbationThreshold;
}
void Convex2DConvex2DAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::set(int value)
{
	Native->m_minimumPointsPerturbationThreshold = value;
}

int Convex2DConvex2DAlgorithm::CreateFunc::NumPerturbationIterations::get()
{
	return Native->m_numPerturbationIterations;
}
void Convex2DConvex2DAlgorithm::CreateFunc::NumPerturbationIterations::set(int value)
{
	Native->m_numPerturbationIterations = value;
}

ConvexPenetrationDepthSolver^ Convex2DConvex2DAlgorithm::CreateFunc::PdSolver::get()
{
	return _pdSolver;
}
void Convex2DConvex2DAlgorithm::CreateFunc::PdSolver::set(ConvexPenetrationDepthSolver^ value)
{
	_pdSolver = value;
	Native->m_pdSolver = value->_native;
}

SimplexSolverInterface^ Convex2DConvex2DAlgorithm::CreateFunc::SimplexSolver::get()
{
	return _simplexSolver;
}
void Convex2DConvex2DAlgorithm::CreateFunc::SimplexSolver::set(SimplexSolverInterface^ value)
{
	_simplexSolver = value;
	Native->m_simplexSolver = value->_native;
}


#undef Native
#define Native static_cast<btConvex2dConvex2dAlgorithm*>(_native)

Convex2DConvex2DAlgorithm::Convex2DConvex2DAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
	: ActivatingCollisionAlgorithm(new btConvex2dConvex2dAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native, simplexSolver->_native,
		pdSolver->_native, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

void Convex2DConvex2DAlgorithm::SetLowLevelOfDetail(bool useLowLevel)
{
	Native->setLowLevelOfDetail(useLowLevel);
}

PersistentManifold Convex2DConvex2DAlgorithm::Manifold::get()
{
	return PersistentManifold((btPersistentManifold*)Native->getManifold());
}

#endif
#endif
