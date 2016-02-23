#pragma once

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	ref class MlcpSolverInterface;

	public ref class MlcpSolver : SequentialImpulseConstraintSolver
	{
	private:
		MlcpSolverInterface^ _mlcpSolver;

	public:
		MlcpSolver(MlcpSolverInterface^ solver);

		void SetMLCPSolver(MlcpSolverInterface^ solver);

		property int NumFallbacks
		{
			int get();
			void set(int num);
		}
	};
};
