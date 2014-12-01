#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexPenetrationDepthSolver.h"
#include "ConvexShape.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConvexPenetrationDepthSolver::ConvexPenetrationDepthSolver(btConvexPenetrationDepthSolver* native)
{
	_native = native;
}

ConvexPenetrationDepthSolver::~ConvexPenetrationDepthSolver()
{
	this->!ConvexPenetrationDepthSolver();
}

ConvexPenetrationDepthSolver::!ConvexPenetrationDepthSolver()
{
	if (this->IsDisposed)
		return;

	delete _native;
	_native = NULL;
}

bool ConvexPenetrationDepthSolver::CalcPenDepth(SimplexSolverInterface^ simplexSolver,
	ConvexShape^ convexA, ConvexShape^ convexB, Matrix transA, Matrix transB,
	[Out] Vector3% v, [Out] Vector3% pa, [Out] Vector3% pb
#ifndef DISABLE_DEBUGDRAW
	, IDebugDraw^ debugDraw
#endif
	)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	btVector3* vTemp = ALIGNED_NEW(btVector3);
	btVector3* paTemp = ALIGNED_NEW(btVector3);
	btVector3* pbTemp = ALIGNED_NEW(btVector3);

	bool ret;
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ debugDrawer = dynamic_cast<DebugDraw^>(debugDraw);
	if (debugDrawer) {
		ret = _native->calcPenDepth(*simplexSolver->_native, (btConvexShape*)convexA->_native,
			(btConvexShape*)convexB->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
			*vTemp, *paTemp, *pbTemp, debugDrawer->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDraw, false);
		ret = _native->calcPenDepth(*simplexSolver->_native, (btConvexShape*)convexA->_native,
			(btConvexShape*)convexB->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
			*vTemp, *paTemp, *pbTemp, wrapper);
		delete wrapper;
	}
#else
	ret = _native->calcPenDepth(*simplexSolver->_native, (btConvexShape*)convexA->_native,
		(btConvexShape*)convexB->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		*vTemp, *paTemp, *pbTemp, 0);
#endif

	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	Math::BtVector3ToVector3(vTemp, v);
	Math::BtVector3ToVector3(paTemp, pa);
	Math::BtVector3ToVector3(pbTemp, pb);
	ALIGNED_FREE(vTemp);
	ALIGNED_FREE(paTemp);
	ALIGNED_FREE(pbTemp);
	return ret;
}

bool ConvexPenetrationDepthSolver::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
