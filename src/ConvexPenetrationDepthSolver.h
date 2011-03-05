#pragma once

// Fully implemented as of 30 Jun 2010

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

	private:
		btConvexPenetrationDepthSolver* _depthSolver;

	internal:
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

	internal:
		property btConvexPenetrationDepthSolver* UnmanagedPointer
		{
			virtual btConvexPenetrationDepthSolver* get();
			void set(btConvexPenetrationDepthSolver* value);
		}
	};
};
