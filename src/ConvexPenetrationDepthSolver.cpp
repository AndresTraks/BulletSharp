#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h>
#pragma managed(pop)

#include "ConvexPenetrationDepthSolver.h"

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
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_depthSolver = NULL;

	OnDisposed( this, nullptr );
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
