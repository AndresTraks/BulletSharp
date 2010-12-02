#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexPenetrationDepthSolver.h"
#include "ConvexShape.h"
#include "StackAlloc.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConvexPenetrationDepthSolver::ConvexPenetrationDepthSolver(btConvexPenetrationDepthSolver* depthSolver)
{
	_depthSolver = depthSolver;
}

ConvexPenetrationDepthSolver::~ConvexPenetrationDepthSolver()
{
	this->!ConvexPenetrationDepthSolver();
}

ConvexPenetrationDepthSolver::!ConvexPenetrationDepthSolver()
{
	if (this->IsDisposed)
		return;

	OnDisposing( this, nullptr );

	_depthSolver = NULL;

	OnDisposed( this, nullptr );
}

bool ConvexPenetrationDepthSolver::CalcPenDepth(SimplexSolverInterface^ simplexSolver,
	ConvexShape^ convexA, ConvexShape^ convexB, Matrix transA, Matrix transB,
	Vector3 v, Vector3 pa, Vector3 pb,
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ debugDraw,
#endif
	StackAlloc^ stackAlloc)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);
	btVector3* vTemp = Math::Vector3ToBtVector3(v);
	btVector3* paTemp = Math::Vector3ToBtVector3(pa);
	btVector3* pbTemp = Math::Vector3ToBtVector3(pb);

	bool ret = _depthSolver->calcPenDepth(*simplexSolver->UnmanagedPointer, convexA->UnmanagedPointer, convexB->UnmanagedPointer,
		*transATemp, *transBTemp, *vTemp, *paTemp, *pbTemp,
#ifndef DISABLE_DEBUGDRAW
		(debugDraw != nullptr) ? debugDraw->UnmanagedPointer : 0,
#else
		0,
#endif
		stackAlloc->UnmanagedPointer);

	delete transATemp;
	delete transBTemp;
	delete vTemp;
	delete paTemp;
	delete pbTemp;

	return ret;
}

bool ConvexPenetrationDepthSolver::IsDisposed::get()
{
	return (_depthSolver == NULL);
}

btConvexPenetrationDepthSolver* ConvexPenetrationDepthSolver::UnmanagedPointer::get()
{
	return _depthSolver;
}
void ConvexPenetrationDepthSolver::UnmanagedPointer::set(btConvexPenetrationDepthSolver* value)
{
	_depthSolver = value;
}

#endif
