#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "ConvexPlaneCollisionAlgorithm.h"
#include "Dispatcher.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

ConvexPlaneCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btConvexPlaneCollisionAlgorithm::CreateFunc())
{
}

int ConvexPlaneCollisionAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::get()
{
	return UnmanagedPointer->m_minimumPointsPerturbationThreshold;
}
void ConvexPlaneCollisionAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::set(int value)
{
	UnmanagedPointer->m_minimumPointsPerturbationThreshold = value;
}

int ConvexPlaneCollisionAlgorithm::CreateFunc::PerturbationIterationsCount::get()
{
	return UnmanagedPointer->m_numPerturbationIterations;
}
void ConvexPlaneCollisionAlgorithm::CreateFunc::PerturbationIterationsCount::set(int value)
{
	UnmanagedPointer->m_numPerturbationIterations = value;
}

btConvexPlaneCollisionAlgorithm::CreateFunc* ConvexPlaneCollisionAlgorithm::CreateFunc::UnmanagedPointer::get()
{
	return (btConvexPlaneCollisionAlgorithm::CreateFunc*)CollisionAlgorithmCreateFunc::UnmanagedPointer;
}


ConvexPlaneCollisionAlgorithm::ConvexPlaneCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
	CollisionObject^ col0, CollisionObject^ col1, bool isSwapped, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: CollisionAlgorithm(new btConvexPlaneCollisionAlgorithm(mf->UnmanagedPointer, *ci->UnmanagedPointer,
	col0->UnmanagedPointer, col1->UnmanagedPointer, isSwapped, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

void ConvexPlaneCollisionAlgorithm::CollideSingleContact(Quaternion perturbeRot, CollisionObject^ body0, CollisionObject^ body1,
	DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut)
{
	btQuaternion* perturbeRotTemp = Math::QuaternionToBtQuat(perturbeRot);
	UnmanagedPointer->collideSingleContact(*perturbeRotTemp, body0->UnmanagedPointer, body1->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, resultOut->UnmanagedPointer);
	delete perturbeRotTemp;
}

btConvexPlaneCollisionAlgorithm* ConvexPlaneCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btConvexPlaneCollisionAlgorithm*)CollisionAlgorithm::UnmanagedPointer;
}

#endif
#endif
