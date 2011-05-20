#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class SphereShape : ConvexInternalShape
	{
	internal:
		SphereShape(btSphereShape* shape);

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
