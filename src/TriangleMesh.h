#pragma once

#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	public ref class TriangleMesh : TriangleIndexVertexArray
	{
	internal:
		TriangleMesh(btTriangleMesh* native);

	public:
		TriangleMesh(bool use32BitIndices, bool use4ComponentVertices);
		TriangleMesh(bool use32BitIndices);
		TriangleMesh();

#ifndef DISABLE_INTERNAL
		void AddIndex(int index);
#endif
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices);
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2);
#ifndef DISABLE_INTERNAL
		void AddTriangleIndices(int index1, int index2, int index3);
		int FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices);
#endif

		property int NumTriangles
		{
			int get();
		}

		property bool Use32BitIndices
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
