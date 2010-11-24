#pragma once

// Fully implemented as of 24 Nov 2010

#include "SequentialImpulseConstraintSolver.h"
#include "ThreadSupportInterface.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class ParallelConstraintSolver : SequentialImpulseConstraintSolver
		{
		public:
			ParallelConstraintSolver(ThreadSupportInterface^ solverThreadSupport);
		};
	};
};
