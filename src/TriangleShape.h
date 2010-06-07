#pragma once

// Fully implemented as of 10 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#pragma managed(pop)

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class TriangleShape : PolyhedralConvexShape
	{
	internal:
		TriangleShape(btTriangleShape* triangleShape);

	public:
		TriangleShape();
		TriangleShape(Vector3 p0, Vector3 p1, Vector3 p2);

		void CalcNormal([Out] Vector3% normal);
		void GetPlaneEquation(int i, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport);
		Vector3 GetVertexPtr(int index);

		property array<Vector3>^ Vertices
		{
			array<Vector3>^ get();
			void set(array<Vector3>^ value);
		}

	internal:
		property btTriangleShape* UnmanagedPointer
		{
			btTriangleShape* get() new;
		}
	};
}
