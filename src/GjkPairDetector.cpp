#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexPenetrationDepthSolver.h"
#include "ConvexShape.h"
#include "GjkPairDetector.h"
#include "SimplexSolverInterface.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

#define Native static_cast<btGjkPairDetector*>(_native)

GjkPairDetector::GjkPairDetector(btGjkPairDetector* native)
	: DiscreteCollisionDetectorInterface(native)
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ penetrationDepthSolver)
	: DiscreteCollisionDetectorInterface(ALIGNED_NEW(btGjkPairDetector) ((btConvexShape*)objectA->_native,
		(btConvexShape*)objectB->_native, simplexSolver->_native, GetUnmanagedNullable(penetrationDepthSolver)))
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, BroadphaseNativeType shapeTypeA,
	BroadphaseNativeType shapeTypeB, btScalar marginA, btScalar marginB, SimplexSolverInterface^ simplexSolver,
	ConvexPenetrationDepthSolver^ penetrationDepthSolver)
	: DiscreteCollisionDetectorInterface(ALIGNED_NEW(btGjkPairDetector) ((btConvexShape*)objectA->_native,
		(btConvexShape*)objectB->_native, (int)shapeTypeA, (int)shapeTypeB, marginA, marginB,
		simplexSolver->_native, GetUnmanagedNullable(penetrationDepthSolver)))
{
}

#ifndef DISABLE_DEBUGDRAW
void GjkPairDetector::GetClosestPointsNonVirtual(ClosestPointInput^ input, Result^ output,
	IDebugDraw^ debugDraw)
{
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(debugDraw);
	if (debugDrawer) {
		Native->getClosestPointsNonVirtual(*input->_native, *output->_native, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDraw, false);
		Native->getClosestPointsNonVirtual(*input->_native, *output->_native, wrapper);
		delete wrapper;
	}
}
#else
void GjkPairDetector::GetClosestPointsNonVirtual(ClosestPointInput^ input, Result^ output)
{
	Native->getClosestPointsNonVirtual(*input->_native, *output->_native, 0);
}
#endif
#ifndef DISABLE_INTERNAL
void GjkPairDetector::SetIgnoreMargin(bool ignoreMargin)
{
	Native->setIgnoreMargin(ignoreMargin);
}
#endif
void GjkPairDetector::SetMinkowskiA(ConvexShape^ minkA)
{
	Native->setMinkowskiA((btConvexShape*)minkA->_native);
}

void GjkPairDetector::SetMinkowskiB(ConvexShape^ minkB)
{
	Native->setMinkowskiB((btConvexShape*)minkB->_native);
}

void GjkPairDetector::SetPenetrationDepthSolver(ConvexPenetrationDepthSolver^ penetrationDepthSolver)
{
	Native->setPenetrationDepthSolver(penetrationDepthSolver->_native);
}

Vector3 GjkPairDetector::CachedSeparatingAxis::get()
{
	return Math::BtVector3ToVector3(&Native->getCachedSeparatingAxis());
}
void GjkPairDetector::CachedSeparatingAxis::set(Vector3 value)
{
	VECTOR3_CONV(value);
	Native->setCachedSeperatingAxis(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

btScalar GjkPairDetector::CachedSeparatingDistance::get()
{
	return Native->getCachedSeparatingDistance();
}

int GjkPairDetector::CatchDegeneracies::get()
{
	return Native->m_catchDegeneracies;
}
void GjkPairDetector::CatchDegeneracies::set(int value)
{
	Native->m_catchDegeneracies = value;
}

int GjkPairDetector::CurIter::get()
{
	return Native->m_curIter;
}
void GjkPairDetector::CurIter::set(int value)
{
	Native->m_curIter = value;
}

int GjkPairDetector::DegenerateSimplex::get()
{
	return Native->m_degenerateSimplex;
}
void GjkPairDetector::DegenerateSimplex::set(int value)
{
	Native->m_degenerateSimplex = value;
}

int GjkPairDetector::FixContactNormalDirection::get()
{
	return Native->m_fixContactNormalDirection;
}
void GjkPairDetector::FixContactNormalDirection::set(int value)
{
	Native->m_fixContactNormalDirection = value;
}

int GjkPairDetector::LastUsedMethod::get()
{
	return Native->m_lastUsedMethod;
}
void GjkPairDetector::LastUsedMethod::set(int value)
{
	Native->m_lastUsedMethod = value;
}

#endif
