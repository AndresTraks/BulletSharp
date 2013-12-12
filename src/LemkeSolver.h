#pragma once

#include "MLCPSolverInterface.h"

namespace BulletSharp
{
	public ref class LemkeSolver : MLCPSolverInterface
	{
	internal:
		LemkeSolver(btLemkeSolver* native);

	public:
		LemkeSolver();

		property int DebugLevel
		{
			int get();
			void set(int value);
		}

		property int MaxLoops
		{
			int get();
			void set(int value);
		}

		property float MaxValue
		{
			float get();
			void set(float value);
		}

		property bool UseLoHighBounds
		{
			bool get();
			void set(bool value);
		}
	};
};
