#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionObjectWrapper.h"
#include "ConvexPlaneCollisionAlgorithm.h"
#include "Dispatcher.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

#define Native static_cast<btConvexPlaneCollisionAlgorithm::CreateFunc*>(_native)

ConvexPlaneCollisionAlgorithm::CreateFunc::CreateFunc(btConvexPlaneCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

ConvexPlaneCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btConvexPlaneCollisionAlgorithm::CreateFunc(), false)
{
}

int ConvexPlaneCollisionAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::get()
{
	return Native->m_minimumPointsPerturbationThreshold;
}
void ConvexPlaneCollisionAlgorithm::CreateFunc::MinimumPointsPerturbationThreshold::set(
	int value)
{
	Native->m_minimumPointsPerturbationThreshold = value;
}

int ConvexPlaneCollisionAlgorithm::CreateFunc::NumPerturbationIterations::get()
{
	return Native->m_numPerturbationIterations;
}
void ConvexPlaneCollisionAlgorithm::CreateFunc::NumPerturbationIterations::set(int value)
{
	Native->m_numPerturbationIterations = value;
}


#undef Native
#define Native static_cast<btConvexPlaneCollisionAlgorithm*>(_native)

ConvexPlaneCollisionAlgorithm::ConvexPlaneCollisionAlgorithm(btConvexPlaneCollisionAlgorithm* native)
	: CollisionAlgorithm(native)
{
}

ConvexPlaneCollisionAlgorithm::ConvexPlaneCollisionAlgorithm(PersistentManifold mf,
	CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
	bool isSwapped, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
	: CollisionAlgorithm(new btConvexPlaneCollisionAlgorithm(mf._native,
		*ci->_native, body0Wrap->_native, body1Wrap->_native, isSwapped, numPerturbationIterations,
		minimumPointsPerturbationThreshold))
{
}

void ConvexPlaneCollisionAlgorithm::CollideSingleContact(Quaternion perturbeRot,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, DispatcherInfo^ dispatchInfo,
	ManifoldResult^ resultOut)
{
	QUATERNION_CONV(perturbeRot);
	Native->collideSingleContact(QUATERNION_USE(perturbeRot), body0Wrap->_native,
		body1Wrap->_native, *dispatchInfo->_native, (btManifoldResult*)resultOut->_native);
	QUATERNION_DEL(perturbeRot);
}

#endif
#endif
