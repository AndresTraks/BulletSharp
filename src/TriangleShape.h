#pragma once

// Fully implemented as of 07 Dec 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class TriangleShape : PolyhedralConvexShape
	{
	private:
		Vector3Array^ _vertices;

	internal:
		TriangleShape(btTriangleShape* triangleShape);

	public:
		TriangleShape();
		TriangleShape(Vector3 point0, Vector3 point1, Vector3 point2);

		void CalcNormal([Out] Vector3% normal);
		void GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport);
		Vector3 GetVertexPtr(int index);

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}

	internal:
		property btTriangleShape* UnmanagedPointer
		{
			btTriangleShape* get() new;
		}
	};
}
