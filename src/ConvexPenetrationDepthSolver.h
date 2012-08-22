#pragma once

#include "IDisposable.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexShape;
	ref class SimplexSolverInterface;
	ref class StackAlloc;
	interface class IDebugDraw;

	public ref class ConvexPenetrationDepthSolver : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btConvexPenetrationDepthSolver* _unmanaged;
		ConvexPenetrationDepthSolver(btConvexPenetrationDepthSolver* depthSolver);

	public:
		!ConvexPenetrationDepthSolver();
	protected:
		~ConvexPenetrationDepthSolver();

	public:
		bool CalcPenDepth(SimplexSolverInterface^ simplexSolver,
			ConvexShape^ convexA, ConvexShape^ convexB, Matrix transA, Matrix transB,
			Vector3 v, Vector3 pa, Vector3 pb,
#ifndef DISABLE_DEBUGDRAW
			IDebugDraw^ debugDraw,
#endif
			StackAlloc^ stackAlloc);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
