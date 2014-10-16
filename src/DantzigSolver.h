#pragma once

#include "MlcpSolverInterface.h"

namespace BulletSharp
{
	public ref class DantzigSolver : MlcpSolverInterface
	{
	internal:
		DantzigSolver(btDantzigSolver* native);

	public:
		DantzigSolver();
	};
};
