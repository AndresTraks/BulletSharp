#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#pragma managed(pop)

#include "DataStream.h"

namespace BulletSharp
{
	ref class ConvexShape;

	public ref class ShapeHull
	{
	private:
		btShapeHull* _shapeHull;

	public:
		ShapeHull(ConvexShape^ shape);

		bool BuildHull(btScalar margin);
		DataStream^ GetIndexStream();
		DataStream^ GetVertexStream();

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
	};
};
