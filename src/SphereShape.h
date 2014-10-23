#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class SphereShape : ConvexInternalShape
	{
	public:
		SphereShape(btScalar radius);

		void SetUnscaledRadius(btScalar radius);

		property btScalar Radius
		{
			btScalar get();
		}
	};
};
