#pragma once

#include "ConstraintSolver.h"
#include "CollisionObject.h"

namespace BulletSharp
{
	public ref class SequentialImpulseConstraintSolver : BulletSharp::ConstraintSolver
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
