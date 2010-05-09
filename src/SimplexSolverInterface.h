#pragma once

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btSimplexSolverInterface.h>
#pragma managed(pop)

#include "IDisposable.h"

#ifdef NO_VIRTUAL_INTERFACE
#include "VoronoiSimplexSolver.h"
#define SimplexSolverInterface VoronoiSimplexSolver
#else

namespace BulletSharp
{
	public ref class SimplexSolverInterface : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

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

	public:

	internal:
		property btSimplexSolverInterface* UnmanagedPointer
		{
			virtual btSimplexSolverInterface* get();
			void set(btSimplexSolverInterface* value);
		}
	};
};
#endif
