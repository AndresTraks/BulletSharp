#pragma once

// Fully implemented as of 10 Apr 2010

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

	internal:
		property btSphereShape* UnmanagedPointer
		{
			btSphereShape* get() new;
		}
	};
};
