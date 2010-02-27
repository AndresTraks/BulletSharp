#pragma once

#include "ConstraintSolver.h"

namespace BulletSharp
{
	ref class CollisionObject;

	public ref class SequentialImpulseConstraintSolver : ConstraintSolver
	{
	public:
		SequentialImpulseConstraintSolver();

		unsigned long Rand2();
		int RandInt2(int n);

		property unsigned long RandSeed
		{
			unsigned long get();
			void set(unsigned long value);
		}

		property btSequentialImpulseConstraintSolver* UnmanagedPointer
		{
			btSequentialImpulseConstraintSolver* get() new;
		}
	};
};
