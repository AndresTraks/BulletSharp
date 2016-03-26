#pragma once

#include "TriangleShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class GimTriangleContact
	{
	internal:
		GIM_TRIANGLE_CONTACT* _native;

		GimTriangleContact(GIM_TRIANGLE_CONTACT* native);

		~GimTriangleContact();
		!GimTriangleContact();

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
	};

	public ref class PrimitiveTriangle
	{
	internal:
		btPrimitiveTriangle* _native;

		PrimitiveTriangle(btPrimitiveTriangle* native);

	private:
		Vector3Array^ _vertices;

		~PrimitiveTriangle();
		!PrimitiveTriangle();

	public:
		PrimitiveTriangle();

		void ApplyTransform(Matrix transform);
		void BuildTriPlane();
		int ClipTriangle(PrimitiveTriangle^ other, array<Vector3>^ clippedPoints);
		bool FindTriangleCollisionClipMethod(PrimitiveTriangle^ other, GimTriangleContact^ contacts);
		void GetEdgePlane(int edgeIndex, [Out] Vector4% plane);
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

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}
	};

	public ref class TriangleShapeEx : TriangleShape
	{
	internal:
		TriangleShapeEx(btTriangleShapeEx* native);

	public:
		TriangleShapeEx();
		TriangleShapeEx(Vector3 p0, Vector3 p1, Vector3 p2);
		TriangleShapeEx(TriangleShapeEx^ other);

		void ApplyTransform(Matrix transform);
		void BuildTriPlane(Vector4 plane);
		bool OverlapTestConservative(TriangleShapeEx^ other);
	};
};
