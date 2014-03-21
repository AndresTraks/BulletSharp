#pragma once

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class SphereShape;
	ref class TriangleShape;

	public ref class SphereTriangleDetector : DiscreteCollisionDetectorInterface
	{
	internal:
		SphereTriangleDetector(::SphereTriangleDetector* native);

	public:
		SphereTriangleDetector(SphereShape^ sphere, TriangleShape^ triangle, btScalar contactBreakingThreshold);

		bool Collide(Vector3 sphereCenter, [Out] Vector3% point, [Out] Vector3% resultNormal, [Out] btScalar% depth,
			[Out] btScalar% timeOfImpact, btScalar contactBreakingThreshold);
	};
};
