#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexPenetrationDepthSolver.h"
#include "ConvexShape.h"
#include "GjkPairDetector.h"
#include "SimplexSolverInterface.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

GjkPairDetector::GjkPairDetector(btGjkPairDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: DiscreteCollisionDetectorInterface(new btGjkPairDetector((btConvexShape*)objectA->_native,
	(btConvexShape*)objectB->_native, simplexSolver->UnmanagedPointer,
	GetUnmanagedNullable(penetrationDepthSolver)))
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, BroadphaseNativeType shapeTypeA,
	BroadphaseNativeType shapeTypeB, btScalar marginA, btScalar marginB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: DiscreteCollisionDetectorInterface(new btGjkPairDetector((btConvexShape*)objectA->_native,
	(btConvexShape*)objectB->_native, (int)shapeTypeA, (int)shapeTypeB,
	marginA, marginB, simplexSolver->UnmanagedPointer,
	GetUnmanagedNullable(penetrationDepthSolver)))
{
}

#ifndef DISABLE_DEBUGDRAW
void GjkPairDetector::GetClosestPointsNonVirtual(
	ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw)
{
	UnmanagedPointer->getClosestPointsNonVirtual(*input->UnmanagedPointer, *output->_native,
		DebugDraw::GetUnmanaged(debugDraw));
}
#else
void GjkPairDetector::GetClosestPointsNonVirtual(
	ClosestPointInput^ input, Result^ output)
{
	UnmanagedPointer->getClosestPointsNonVirtual(*input->UnmanagedPointer, *output->_native, 0);
}
#endif

void GjkPairDetector::SetMinkowskiA(ConvexShape^ minkA)
{
	UnmanagedPointer->setMinkowskiA((btConvexShape*)minkA->_native);
}

void GjkPairDetector::SetMinkowskiB(ConvexShape^ minkB)
{
	UnmanagedPointer->setMinkowskiB((btConvexShape*)minkB->_native);
}

void GjkPairDetector::SetPenetrationDepthSolver(ConvexPenetrationDepthSolver^ penetrationDepthSolver)
{
	UnmanagedPointer->setPenetrationDepthSolver(penetrationDepthSolver->_native);
}

Vector3 GjkPairDetector::CachedSeparatingAxis::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getCachedSeparatingAxis());
}
void GjkPairDetector::CachedSeparatingAxis::set(Vector3 value)
{
	VECTOR3_DEF(value);
	UnmanagedPointer->setCachedSeperatingAxis(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

btScalar GjkPairDetector::CachedSeparatingDistance::get()
{
	return UnmanagedPointer->getCachedSeparatingDistance();
}

int GjkPairDetector::CatchDegeneracies::get()
{
	return UnmanagedPointer->m_catchDegeneracies;
}
void GjkPairDetector::CatchDegeneracies::set(int value)
{
	UnmanagedPointer->m_catchDegeneracies = value;
}

int GjkPairDetector::CurIter::get()
{
	return UnmanagedPointer->m_curIter;
}
void GjkPairDetector::CurIter::set(int value)
{
	UnmanagedPointer->m_curIter = value;
}

int GjkPairDetector::DegenerateSimplex::get()
{
	return UnmanagedPointer->m_degenerateSimplex;
}
void GjkPairDetector::DegenerateSimplex::set(int value)
{
	UnmanagedPointer->m_degenerateSimplex = value;
}

int GjkPairDetector::LastUsedMethod::get()
{
	return UnmanagedPointer->m_lastUsedMethod;
}
void GjkPairDetector::LastUsedMethod::set(int value)
{
	UnmanagedPointer->m_lastUsedMethod = value;
}

btGjkPairDetector* GjkPairDetector::UnmanagedPointer::get()
{
	return (btGjkPairDetector*)DiscreteCollisionDetectorInterface::UnmanagedPointer;
}

#endif
