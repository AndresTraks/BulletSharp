#pragma once

// Fully implemented as of 23 Nov 2010

#include "TriangleShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class GimTriangleContact
	{
	private:
		GIM_TRIANGLE_CONTACT* _contact;

	public:
		GimTriangleContact();
		GimTriangleContact(GimTriangleContact^ other);

		void CopyFrom(GimTriangleContact^ other);
		void MergePoints(Vector4 plane, btScalar margin, array<Vector3>^ points);

		property btScalar PenetrationDepth
		{
			btScalar get();
			void set(btScalar value);
		}

		property int PointCount
		{
			int get();
			void set(int value);
		}

		property Vector3Array^ Points
		{
			Vector3Array^ get();
		}

		property Vector4 SeparatingNormal
		{
			Vector4 get();
			void set(Vector4 value);
		}

	internal:
		property GIM_TRIANGLE_CONTACT* UnmanagedPointer
		{
			GIM_TRIANGLE_CONTACT* get();
			void set(GIM_TRIANGLE_CONTACT* value);
		}
	};

	public ref class PrimitiveTriangle
	{
	private:
		btPrimitiveTriangle* _triangle;

	internal:
		PrimitiveTriangle(btPrimitiveTriangle* triangle);

	public:
		PrimitiveTriangle();

		void ApplyTransform(Matrix transform);
		void BuildTriPlane();
		int ClipTriangle(PrimitiveTriangle^ other, array<Vector3>^ clippedPoints);
		bool FindTriangleCollisionClipMethod(PrimitiveTriangle^ other, GimTriangleContact^ contacts);
		void GetEdgePlane(int edge_index, [Out] Vector4% plane);
		bool OverlapTestConservative(PrimitiveTriangle^ other);

		property btScalar Dummy
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Margin
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector4 Plane
		{
			Vector4 get();
			void set(Vector4 value);
		}

		property Vector3Array^ Vectors
		{
			Vector3Array^ get();
		}

	internal:
		property btPrimitiveTriangle* UnmanagedPointer
		{
			btPrimitiveTriangle* get();
			void set(btPrimitiveTriangle* value);
		}
	};

	public ref class TriangleShapeEx : TriangleShape
	{
	internal:
		TriangleShapeEx(btTriangleShapeEx* triangle);

	public:
		TriangleShapeEx();
		TriangleShapeEx(Vector3 p0, Vector3 p1, Vector3 p2);
		TriangleShapeEx(TriangleShapeEx^ other);

		void ApplyTransform(Matrix transform);
		void BuildTriPlane(Vector4 plane);
		bool OverlapTestConservative(TriangleShapeEx^ other);

	internal:
		property btTriangleShapeEx* UnmanagedPointer
		{
			btTriangleShapeEx* get();
		}
	};
};
