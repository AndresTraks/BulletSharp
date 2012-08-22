#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	ref class TriangleCallback;

	public ref class ConcaveShape abstract : CollisionShape
	{
	internal:
		ConcaveShape(btConcaveShape* concaveShape);

	public:
		void ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax);
	};
};
