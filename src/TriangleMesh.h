#pragma once

#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	public ref class TriangleMesh : TriangleIndexVertexArray
	{
	internal:
		TriangleMesh(btTriangleMesh* native);

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

		property int NumTriangles
		{
			int get();
		}

		property bool Use32BitIndexes
		{
			bool get();
		}

		property bool Use4ComponentVertices
		{
			bool get();
		}

		property btScalar WeldingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}
	};
};
