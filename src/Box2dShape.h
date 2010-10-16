#pragma once

// Fully implemented as of 10 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#pragma managed(pop)

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class Box2dShape : PolyhedralConvexShape
	{
	internal:
		Box2dShape(btBox2dShape* shape);

	public:
		Box2dShape(Vector3 boxHalfExtents);
		Box2dShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ);
		Box2dShape(btScalar boxHalfExtent); // cube helper

		static Box2dShape^ Upcast(CollisionShape^ shape);

		Vector4 GetPlaneEquation(int i);
		Vector3 GetVertex(int i);

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

		property int VertexCount
		{
			int get();
		}

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}

	internal:
		property btBox2dShape* UnmanagedPointer
		{
			btBox2dShape* get() new;
		}
	};
};
