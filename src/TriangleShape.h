#pragma once

// Fully implemented as of 10 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#pragma managed(pop)

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3List;

	public ref class TriangleShape : PolyhedralConvexShape
	{
	internal:
		TriangleShape(btTriangleShape* triangleShape);

	public:
		TriangleShape();
		TriangleShape(Vector3 point0, Vector3 point1, Vector3 point2);

		void CalcNormal([Out] Vector3% normal);
		void GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport);
		Vector3 GetVertexPtr(int index);

		property Vector3List^ Vertices
		{
			Vector3List^ get();
		}

	internal:
		property btTriangleShape* UnmanagedPointer
		{
			btTriangleShape* get() new;
		}
	};
}
