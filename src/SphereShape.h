#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class SphereShape : BulletSharp::ConvexInternalShape
	{
		public:
			SphereShape(btScalar radius);
	};
};
