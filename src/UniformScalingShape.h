#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class UniformScalingShape : ConvexShape
	{
	private:
		ConvexShape^ _childShape;

	public:
		UniformScalingShape(ConvexShape^ convexChildShape, btScalar uniformScalingFactor);

		property ConvexShape^ ChildShape
		{
			ConvexShape^ get();
		}

		property btScalar UniformScalingFactor
		{
			btScalar get();
		}
	};
};
