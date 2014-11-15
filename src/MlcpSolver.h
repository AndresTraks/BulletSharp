#pragma once

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	ref class MlcpSolverInterface;

	public ref class MlcpSolver : SequentialImpulseConstraintSolver
	{
	private:
		MlcpSolverInterface^ _mlcpSolver;

	internal:
		MlcpSolver(btMLCPSolver* native);

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
