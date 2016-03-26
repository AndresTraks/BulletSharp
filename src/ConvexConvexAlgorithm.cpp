#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ConvexConvexAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"

#define Native static_cast<btConvexConvexAlgorithm::CreateFunc*>(_native)

ConvexConvexAlgorithm::CreateFunc::CreateFunc(btConvexConvexAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

ConvexConvexAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver)
	: CollisionAlgorithmCreateFunc(new btConvexConvexAlgorithm::CreateFunc(simplexSolver->_native,
		pdSolver->_native), false)
{
	_pdSolver = pdSolver;
	_simplexSolver = simplexSolver;
}

int ConvexConvexAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::get()
{
	return Native->m_minimumPointsPerturbationThreshold;
}
void ConvexConvexAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::set(int value)
{
	Native->m_minimumPointsPerturbationThreshold = value;
}

int ConvexConvexAlgorithm::CreateFunc::NumPerturbationIterations::get()
{
	return Native->m_numPerturbationIterations;
}
void ConvexConvexAlgorithm::CreateFunc::NumPerturbationIterations::set(int value)
{
	Native->m_numPerturbationIterations = value;
}

ConvexPenetrationDepthSolver^ ConvexConvexAlgorithm::CreateFunc::PdSolver::get()
{
	return _pdSolver;
}
void ConvexConvexAlgorithm::CreateFunc::PdSolver::set(ConvexPenetrationDepthSolver^ value)
{
	_pdSolver = value;
	Native->m_pdSolver = value->_native;
}

SimplexSolverInterface^ ConvexConvexAlgorithm::CreateFunc::SimplexSolver::get()
{
	return _simplexSolver;
}
void ConvexConvexAlgorithm::CreateFunc::SimplexSolver::set(SimplexSolverInterface^ value)
{
	_simplexSolver = value;
	Native->m_simplexSolver = value->_native;
}


#undef Native
#define Native static_cast<btConvexConvexAlgorithm*>(_native)

ConvexConvexAlgorithm::ConvexConvexAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
	: ActivatingCollisionAlgorithm(new btConvexConvexAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native, simplexSolver->_native,
		pdSolver->_native, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

void ConvexConvexAlgorithm::SetLowLevelOfDetail(bool useLowLevel)
{
	Native->setLowLevelOfDetail(useLowLevel);
}

PersistentManifold ConvexConvexAlgorithm::Manifold::get()
{
	return PersistentManifold((btPersistentManifold*)Native->getManifold());
}

#endif
#endif
