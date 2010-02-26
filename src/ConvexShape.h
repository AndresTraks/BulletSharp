#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	public ref class ConvexShape : CollisionShape
	{
	internal:
		ConvexShape(btConvexShape* convexShape);

	public:
		static ConvexShape^ Upcast(CollisionShape^ shape);

	internal:
		property btConvexShape* UnmanagedPointer
		{
			btConvexShape* get() new;
		}
	};
};
