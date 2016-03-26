#pragma once

#include "DataStream.h"

namespace BulletSharp
{
	ref class ConvexShape;
	ref class UIntArray;
	ref class Vector3Array;

	public ref class ShapeHull
	{
	internal:
		btShapeHull* _native;

	private:
		ConvexShape^ _shape;

		~ShapeHull();
		!ShapeHull();

	public:
		ShapeHull(ConvexShape^ shape);

		bool BuildHull(btScalar margin);
		DataStream^ GetIndexStream();
		DataStream^ GetVertexStream();

		property UIntArray^ Indices
		{
			UIntArray^ get();
		}

		property int NumIndices
		{
			int get();
		}

		property int NumTriangles
		{
			int get();
		}

		property int NumVertices
		{
			int get();
		}

		property Vector3Array^ Vertices
		{
			Vector3Array^ get();
		}
	};
};
