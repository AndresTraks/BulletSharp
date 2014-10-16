#pragma once

#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexShape;
	ref class SimplexSolverInterface;
	interface class IDebugDraw;

	public ref class ConvexPenetrationDepthSolver : IDisposable // abstract
	{
	internal:
		btConvexPenetrationDepthSolver* _native;
		ConvexPenetrationDepthSolver(btConvexPenetrationDepthSolver* native);

	public:
		!ConvexPenetrationDepthSolver();
	protected:
		~ConvexPenetrationDepthSolver();

	public:
		bool CalcPenDepth(SimplexSolverInterface^ simplexSolver, ConvexShape^ convexA,
			ConvexShape^ convexB, Matrix transA, Matrix transB, [Out] Vector3% v, [Out] Vector3% pa,
			[Out] Vector3% pb
#ifndef DISABLE_DEBUGDRAW
			, IDebugDraw^ debugDraw
#endif
			);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
