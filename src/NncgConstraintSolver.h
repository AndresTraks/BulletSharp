#pragma once

#include "SequentialImpulseConstraintSolver.h"

namespace BulletSharp
{
	public ref class NncgConstraintSolver : SequentialImpulseConstraintSolver
	{
	internal:
		NncgConstraintSolver(btNNCGConstraintSolver* native);

	public:
		NncgConstraintSolver();

		property bool OnlyForNoneContact
		{
			bool get();
			void set(bool value);
		}
	};
};
