#pragma once

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
