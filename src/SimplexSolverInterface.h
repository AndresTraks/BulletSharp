#pragma once

#ifdef NO_VIRTUAL_INTERFACE
#include "VoronoiSimplexSolver.h"
#define SimplexSolverInterface VoronoiSimplexSolver
#else

namespace BulletSharp
{
	public ref class SimplexSolverInterface
	{
	internal:
		btSimplexSolverInterface* _native;

		SimplexSolverInterface(btSimplexSolverInterface* simplexSolver);

	public:
		!SimplexSolverInterface();
	protected:
		~SimplexSolverInterface();

	public:
		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
#endif
