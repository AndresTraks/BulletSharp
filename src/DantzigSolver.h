#pragma once

#include "MLCPSolverInterface.h"

namespace BulletSharp
{
	public ref class DantzigSolver : MLCPSolverInterface
	{
	internal:
		DantzigSolver(btDantzigSolver* native);

	public:
		DantzigSolver();
	};
};
