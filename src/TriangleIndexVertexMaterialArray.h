#pragma once

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h>
#pragma managed(pop)

#include "Enums.h"
#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	public ref class TriangleIndexVertexMaterialArray : TriangleIndexVertexArray
	{
	internal:
		TriangleIndexVertexMaterialArray(btTriangleIndexVertexMaterialArray* triangleArray);

	public:
		TriangleIndexVertexMaterialArray();
		TriangleIndexVertexMaterialArray(int numTriangles, IntPtr triangleIndexBase,
			int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride,
			int numMaterials, IntPtr materialBase, int materialStride, IntPtr triangleMaterialsBase,
			int materialIndexStride);
	};
};
