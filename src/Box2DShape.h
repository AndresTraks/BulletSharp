#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class Box2DShape : PolyhedralConvexShape
	{
	private:
		Vector3Array^ _normals;
		Vector3Array^ _vertices;

	public:
		Box2DShape(Vector3 boxHalfExtents);
		Box2DShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ);
		Box2DShape(btScalar boxHalfExtent); // cube helper

		Vector4 GetPlaneEquation(int i);

		property Vector3 Centroid
		{
			Vector3 get();
		}

		property Vector3 HalfExtentsWithMargin
		{
			Vector3 get();
		}

		property Vector3 HalfExtentsWithoutMargin
		{
			Vector3 get();
		}

		property Vector3Array^ Normals
		{
			Vector3Array^ get();
		}

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}
	};
};
