#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class BoxShape : PolyhedralConvexShape
	{
	internal:
		BoxShape(btBoxShape* shape);

	public:
		BoxShape(Vector3 boxHalfExtents);
		BoxShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ);
		BoxShape(btScalar boxHalfExtent); // cube helper

		static BoxShape^ Upcast(CollisionShape^ shape);

		Vector4 GetPlaneEquation(int index);

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
