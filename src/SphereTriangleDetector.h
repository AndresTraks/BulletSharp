#pragma once

// Fully implemented as of 10 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/SphereTriangleDetector.h>
#pragma managed(pop)

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
