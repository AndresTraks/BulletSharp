#pragma once

#include "DiscreteCollisionDetectorInterface.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class ConvexShape;

	public ref class GjkPairDetector : DiscreteCollisionDetectorInterface
	{
	internal:
		GjkPairDetector(btGjkPairDetector* detector);
	
	public:
		GjkPairDetector(ConvexShape^ objectA, ConvexShape^ objectB,
			SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ penetrationDepthSolver);

		property Vector3 CachedSeparatingAxis
		{
			Vector3 get();
			void set(Vector3 value);
		}

	internal:
		property btGjkPairDetector* UnmanagedPointer
		{
			virtual btGjkPairDetector* get() new;
		}
	};
};
