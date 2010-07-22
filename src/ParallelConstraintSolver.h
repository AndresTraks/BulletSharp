#pragma once

// Fully implemented as of 22 jul 2010

#include "SequentialImpulseConstraintSolver.h"
#include "ThreadSupportInterface.h"

#pragma managed(push, off)
#include <BulletMultiThreaded/btParallelConstraintSolver.h>
#pragma managed(pop)

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
