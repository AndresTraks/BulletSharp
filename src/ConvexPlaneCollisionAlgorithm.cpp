#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
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
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
: CollisionAlgorithm(new btConvexPlaneCollisionAlgorithm((btPersistentManifold*)GetUnmanagedNullable(mf), *ci->_unmanaged,
	body0Wrap->_unmanaged, body1Wrap->_unmanaged, isSwapped, numPerturbationIterations, minimumPointsPerturbationThreshold))
{
}

void ConvexPlaneCollisionAlgorithm::CollideSingleContact(Quaternion perturbeRot, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut)
{
	btQuaternion* perturbeRotTemp = Math::QuaternionToBtQuat(perturbeRot);
	UnmanagedPointer->collideSingleContact(*perturbeRotTemp, body0Wrap->_unmanaged, body1Wrap->_unmanaged,
		*dispatchInfo->UnmanagedPointer, resultOut->UnmanagedPointer);
	delete perturbeRotTemp;
}

btConvexPlaneCollisionAlgorithm* ConvexPlaneCollisionAlgorithm::UnmanagedPointer::get()
{
	return (btConvexPlaneCollisionAlgorithm*)CollisionAlgorithm::UnmanagedPointer;
}

#endif
#endif
