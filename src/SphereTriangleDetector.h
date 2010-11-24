#pragma once

// Fully implemented as of 24 Nov 2010

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class SphereShape;
	ref class TriangleShape;

	public ref class SphereTriangleDetector : DiscreteCollisionDetectorInterface
	{
	internal:
		SphereTriangleDetector(::SphereTriangleDetector* detector);

	public:
		SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle, btScalar contactBreakingThreshold);

	internal:
		property ::SphereTriangleDetector* UnmanagedPointer
		{
			::SphereTriangleDetector* get() new;
		}
	};
};
