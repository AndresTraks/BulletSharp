#pragma once

#include "SoftBodySolver.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class OpenCLSoftBodySolver : SoftBody::SoftBodySolver
		{
		public:
			OpenCLSoftBodySolver(IntPtr queue, IntPtr context);
		};
	};

	namespace SoftBody
	{
		public ref class SoftBodySolverOutputCLToCpu : SoftBodySolverOutput
		{
		public:
			SoftBodySolverOutputCLToCpu();
		};
	};
};
