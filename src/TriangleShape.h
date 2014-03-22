#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class TriangleShape : PolyhedralConvexShape
	{
	private:
		Vector3Array^ _vertices;

	internal:
		TriangleShape(btTriangleShape* native);

	public:
		TriangleShape();
		TriangleShape(Vector3 point0, Vector3 point1, Vector3 point2);

		void CalcNormal([Out] Vector3% normal);
		void GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport);
		//IntPtr GetVertexPtr(int index);

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}
	};
};
