#pragma once

#include "TriangleCallback.h"

namespace BulletSharp
{
	public ref struct BulletTriangle
	{
	internal:
		BulletTriangle(const btTriangle* triangle);

	public:
		BulletTriangle();
		BulletTriangle(const BulletTriangle^ &triangle);

		Vector3 vertex0;
		Vector3 vertex1;
		Vector3 vertex2;
		int partId;
		int triangleIndex;
	};

	public ref class TriangleBuffer : TriangleCallback
	{
	public:
		TriangleBuffer();

		void ClearBuffer();
		BulletTriangle^ GetTriangle(int index);

		property int NumTriangles
		{
			int get();
		}
	};
};
