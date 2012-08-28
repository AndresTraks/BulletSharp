#pragma once

#include "IDisposable.h"

#ifdef NO_VIRTUAL_INTERFACE
#include "VoronoiSimplexSolver.h"
#define SimplexSolverInterface VoronoiSimplexSolver
#else

namespace BulletSharp
{
	public ref class SimplexSolverInterface
	{
	private:
		btSimplexSolverInterface* _simplexSolver;

	internal:
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

	internal:
		property btSimplexSolverInterface* UnmanagedPointer
		{
			virtual btSimplexSolverInterface* get();
			void set(btSimplexSolverInterface* value);
		}
	};
};
#endif
