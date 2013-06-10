#pragma once

#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	public ref class TriangleMesh : TriangleIndexVertexArray
	{
	internal:
		TriangleMesh(btTriangleMesh* mesh);

	public:
		TriangleMesh(bool use32BitIndexes, bool use4ComponentVertices);
		TriangleMesh(bool use32BitIndexes);
		TriangleMesh();

#ifndef DISABLE_INTERNAL
		void AddIndex(int index);
		int FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices);
#endif
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices);
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2);
		void PreallocateIndexes(int indexCount);
		void PreallocateVertices(int vertexCount);

		property int TriangleCount
		{
			int get();
		}

		property int Use32BitIndexes
		{
			int get();
		}

		property int Use4ComponentVertices
		{
			int get();
		}

		property btScalar WeldingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}
	};
};
