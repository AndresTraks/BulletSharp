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
	_native = depthSolver;
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

	delete _native;
	_native = NULL;

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

	bool ret = _native->calcPenDepth(*simplexSolver->UnmanagedPointer,
		(btConvexShape*)convexA->_native, (btConvexShape*)convexB->_native,
		*transATemp, *transBTemp, VECTOR3_USE(v), VECTOR3_USE(pa), VECTOR3_USE(pb),
#ifndef DISABLE_DEBUGDRAW
		DebugDraw::GetUnmanaged(debugDraw),
#else
		0,
#endif
		stackAlloc->UnmanagedPointer);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
	VECTOR3_DEL(v);
	VECTOR3_DEL(pa);
	VECTOR3_DEL(pb);

	return ret;
}

bool ConvexPenetrationDepthSolver::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
