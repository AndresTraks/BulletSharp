#pragma once

#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	public ref class TriangleMesh : TriangleIndexVertexArray
	{
	internal:
		TriangleMesh(btTriangleMesh* mesh);

	public:
		TriangleMesh(bool use32bitIndices, bool use4componentVertices);
		TriangleMesh(bool use32bitIndices);
		TriangleMesh();

#ifndef DISABLE_INTERNAL
		void AddIndex(int index);
		int FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices);
#endif
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices);
		void AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2);
		void PreallocateIndices(int numIndices);
		void PreallocateVertices(int numVertices);

		property int NumTriangles
		{
			int get();
		}

		property int Use32bitIndices
		{
			int get();
		}

		property int Use4componentVertices
		{
			int get();
		}

		property btScalar WeldingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

	internal:
		property btTriangleMesh* UnmanagedPointer
		{
			btTriangleMesh* get() new;
		}
	};
};
