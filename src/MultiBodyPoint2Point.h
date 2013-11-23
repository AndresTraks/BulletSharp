#pragma once

#include "MultiBodyConstraint.h"

namespace BulletSharp
{
	ref class MultiBody;
	ref class RigidBody;

	public ref class MultiBodyPoint2Point : MultiBodyConstraint
	{
	internal:
		MultiBodyPoint2Point(btMultiBodyPoint2Point* native);

	public:
		MultiBodyPoint2Point(MultiBody^ body, int link, RigidBody^ bodyB, Vector3 pivotInA, Vector3 pivotInB);
		MultiBodyPoint2Point(MultiBody^ bodyA, int linkA, MultiBody^ bodyB, int linkB, Vector3 pivotInA, Vector3 pivotInB);

		property Vector3 PivotInB
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};
};
