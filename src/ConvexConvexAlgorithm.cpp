#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ConvexConvexAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"

ConvexConvexAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ pdSolver)
: CollisionAlgorithmCreateFunc(new btConvexConvexAlgorithm::CreateFunc(simplexSolver->UnmanagedPointer, pdSolver->_unmanaged))
{
}

int ConvexConvexAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::get()
{
	return UnmanagedPointer->m_minimumPointsPerturbationThreshold;
}
void ConvexConvexAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::set(int value)
{
	UnmanagedPointer->m_minimumPointsPerturbationThreshold = value;
}

int ConvexConvexAlgorithm::CreateFunc::NumPerturbationIterations::get()
{
	return UnmanagedPointer->m_numPerturbationIterations;
}
void ConvexConvexAlgorithm::CreateFunc::NumPerturbationIterations::set(int value)
{
	UnmanagedPointer->m_numPerturbationIterations = value;
}

ConvexPenetrationDepthSolver^ ConvexConvexAlgorithm::CreateFunc::PdSolver::get()
{
	return gcnew ConvexPenetrationDepthSolver(UnmanagedPointer->m_pdSolver);
}
void ConvexConvexAlgorithm::CreateFunc::PdSolver::set(ConvexPenetrationDepthSolver^ value)
{
	UnmanagedPointer->m_pdSolver = value->_unmanaged;
}

SimplexSolverInterface^ ConvexConvexAlgorithm::CreateFunc::SimplexSolver::get()
{
	return gcnew SimplexSolverInterface(UnmanagedPointer->m_simplexSolver);
}
void ConvexConvexAlgorithm::CreateFunc::SimplexSolver::set(SimplexSolverInterface^ value)
{
	UnmanagedPointer->m_simplexSolver = value->UnmanagedPointer;
}

btConvexConvexAlgorithm::CreateFunc* ConvexConvexAlgorithm::CreateFunc::UnmanagedPointer::get()
{
	return (btConvexConvexAlgorithm::CreateFunc*)CollisionAlgorithmCreateFunc::UnmanagedPointer;
}


ConvexConvexAlgorithm::ConvexConvexAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: ActivatingCollisionAlgorithm(new btConvexConvexAlgorithm((btPersistentManifold*)GetUnmanagedNullable(mf),
	*ci->_unmanaged, body0Wrap->_unmanaged, body1Wrap->_unmanaged, simplexSolver->UnmanagedPointer,
	pdSolver->_unmanaged, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

void ConvexConvexAlgorithm::SetLowLevelOfDetail(bool useLowLevel)
{
	UnmanagedPointer->setLowLevelOfDetail(useLowLevel);
}

PersistentManifold^ ConvexConvexAlgorithm::Manifold::get()
{
	return gcnew PersistentManifold((btPersistentManifold*)UnmanagedPointer->getManifold());
}

btConvexConvexAlgorithm* ConvexConvexAlgorithm::UnmanagedPointer::get()
{
	return (btConvexConvexAlgorithm*)ActivatingCollisionAlgorithm::UnmanagedPointer;
}

#endif
#endif
