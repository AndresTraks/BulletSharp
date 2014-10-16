#pragma once

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	ref class MlcpSolverInterface;

	public ref class MlcpSolver : SequentialImpulseConstraintSolver
	{
	internal:
		MlcpSolver(btMLCPSolver* native);

	private:
		MlcpSolverInterface^ _mlcpSolver;

	public:
		MlcpSolver(MlcpSolverInterface^ solver);

		void SetMLCPSolver(MlcpSolverInterface^ solver);

		property btScalar Cfm
		{
			btScalar get();
			void set(btScalar cfm);
		}

		property int NumFallbacks
		{
			int get();
			void set(int num);
		}
	};
};
