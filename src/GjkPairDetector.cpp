#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#pragma managed(pop)

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
: DiscreteCollisionDetectorInterface(new btGjkPairDetector(objectA->UnmanagedPointer,
	objectB->UnmanagedPointer, simplexSolver->UnmanagedPointer,
	(penetrationDepthSolver != nullptr) ? penetrationDepthSolver->UnmanagedPointer : 0))
{
}

GjkPairDetector::GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB, BroadphaseNativeType shapeTypeA,
	BroadphaseNativeType shapeTypeB, btScalar marginA, btScalar marginB,
	SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver)
: DiscreteCollisionDetectorInterface(new btGjkPairDetector(objectA->UnmanagedPointer,
	objectB->UnmanagedPointer, (int)shapeTypeA, (int)shapeTypeB,
	marginA, marginB, simplexSolver->UnmanagedPointer,
	(penetrationDepthSolver != nullptr) ? penetrationDepthSolver->UnmanagedPointer : 0))
{
}

#ifndef DISABLE_DEBUGDRAW
void GjkPairDetector::GetClosestPointsNonVirtual(
	ClosestPointInput^ input, Result^ output, DebugDraw^ debugDraw)
{
	UnmanagedPointer->getClosestPointsNonVirtual(*input->UnmanagedPointer, *output->UnmanagedPointer,
		(debugDraw != nullptr) ? debugDraw->UnmanagedPointer : 0);
}
#else
void GjkPairDetector::GetClosestPointsNonVirtual(
	ClosestPointInput^ input, Result^ output)
{
	UnmanagedPointer->getClosestPointsNonVirtual(*input->UnmanagedPointer, *output->UnmanagedPointer, 0);
}
#endif

void GjkPairDetector::SetMinkowskiA(ConvexShape^ minkA)
{
	UnmanagedPointer->setMinkowskiA(minkA->UnmanagedPointer);
}

void GjkPairDetector::SetMinkowskiB(ConvexShape^ minkB)
{
	UnmanagedPointer->setMinkowskiB(minkB->UnmanagedPointer);
}

void GjkPairDetector::SetPenetrationDepthSolver(ConvexPenetrationDepthSolver^ penetrationDepthSolver)
{
	UnmanagedPointer->setPenetrationDepthSolver(penetrationDepthSolver->UnmanagedPointer);
}

Vector3 GjkPairDetector::CachedSeparatingAxis::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getCachedSeparatingAxis());
}
void GjkPairDetector::CachedSeparatingAxis::set(Vector3 value)
{
	UnmanagedPointer->setCachedSeperatingAxis(*Math::Vector3ToBtVector3(value));
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
