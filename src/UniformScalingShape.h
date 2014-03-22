#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class UniformScalingShape : ConvexShape
	{
	internal:
		UniformScalingShape(btUniformScalingShape* native);

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
