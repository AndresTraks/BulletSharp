#pragma once

// Fully implemented as of 10 Mar 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class BoxShape : PolyhedralConvexShape
	{
	internal:
		BoxShape(btBoxShape* shape);
	public:
		BoxShape(Vector3 boxHalfExtents);
		BoxShape(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ);
		BoxShape(float boxHalfExtent); // cube helper

		static BoxShape^ Upcast(CollisionShape^ shape);

		property Vector3 HalfExtentsWithMargin
		{
			Vector3 get();
		}

		property Vector3 HalfExtentsWithoutMargin
		{
			Vector3 get();
		}

	internal:
		property btBoxShape* UnmanagedPointer
		{
			btBoxShape* get() new;
		}
	};
};
