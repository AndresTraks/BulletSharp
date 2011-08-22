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

		internal:
			property btOpenCLSoftBodySolver* UnmanagedPointer
			{
				btOpenCLSoftBodySolver* get() new;
			}
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
