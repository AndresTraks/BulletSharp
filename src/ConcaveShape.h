#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	public ref class ConcaveShape abstract : CollisionShape
	{
	public:
		//void ProcessAllTriangles(TriangleCallback^ callback,Vector3 aabbMin, Vector3 aabbMax);

	internal:
		ConcaveShape(btConcaveShape* concaveShape);

		property btConcaveShape* UnmanagedPointer
		{
			btConcaveShape* get();
		}
	};
};
