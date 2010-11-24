#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "ConvexConvexAlgorithm.h"
#include "ConvexPenetrationDepthSolver.h"
#include "PersistentManifold.h"

ConvexConvexAlgorithm::CreateFunc::CreateFunc(SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ pdSolver)
: CollisionAlgorithmCreateFunc(new btConvexConvexAlgorithm::CreateFunc(simplexSolver->UnmanagedPointer, pdSolver->UnmanagedPointer))
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
	UnmanagedPointer->m_pdSolver = value->UnmanagedPointer;
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
	CollisionObject^ body0, CollisionObject^ body1, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: ActivatingCollisionAlgorithm(new btConvexConvexAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer, body0->UnmanagedPointer,
	body1->UnmanagedPointer, simplexSolver->UnmanagedPointer, pdSolver->UnmanagedPointer,
	numPerturbationIterations, minimumPointsPerturbationThreshold))
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
