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

	OnDisposing(this, nullptr);

	_depthSolver = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexPenetrationDepthSolver::CalcPenDepth(SimplexSolverInterface^ simplexSolver,
	ConvexShape^ convexA, ConvexShape^ convexB, Matrix transA, Matrix transB,
	Vector3 v, Vector3 pa, Vector3 pb,
#ifndef DISABLE_DEBUGDRAW
	IDebugDraw^ debugDraw,
#endif
	StackAlloc^ stackAlloc)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);
	VECTOR3_DEF(v);
	VECTOR3_DEF(pa);
	VECTOR3_DEF(pb);

	bool ret = _depthSolver->calcPenDepth(*simplexSolver->UnmanagedPointer, convexA->UnmanagedPointer, convexB->UnmanagedPointer,
		*transATemp, *transBTemp, VECTOR3_USE(v), VECTOR3_USE(pa), VECTOR3_USE(pb),
#ifndef DISABLE_DEBUGDRAW
		DebugDraw::GetUnmanaged(debugDraw),
#else
		0,
#endif
		stackAlloc->UnmanagedPointer);

	delete transATemp;
	delete transBTemp;
	VECTOR3_DEL(v);
	VECTOR3_DEL(pa);
	VECTOR3_DEL(pb);

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
