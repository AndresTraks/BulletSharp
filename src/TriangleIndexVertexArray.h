#pragma once

// Fully implemented as of 29 May 2010

#include "Enums.h"
#include "StridingMeshInterface.h"

namespace BulletSharp
{
	ref class AlignedIndexedMeshArray;
	ref class DataStream;
	ref class IntArray;
	ref class Vector3Array;

	public ref class IndexedMesh
	{
	private:
		btIndexedMesh* _indexedMesh;

	internal:
		IndexedMesh(btIndexedMesh* indexedMesh);

	public:
		IndexedMesh();

		void Allocate(int numVerts, int vertexStride, int numIndices, int indexStride);
		void AllocateVerts(int num, int stride);
		void AllocateIndices(int num, int stride);

		DataStream^ LockVerts();
		DataStream^ LockIndices();

		property PhyScalarType IndexType
		{
			PhyScalarType get();
			void set(PhyScalarType value);
		}

		property int NumTriangles
		{
			int get();
			void set(int value);
		}

		property int NumVertices
		{
			int get();
			void set(int value);
		}

		property IntArray^ TriangleIndexBase
		{
			IntArray^ get();
			void set(IntArray^ value);
		}

		property int TriangleIndexStride
		{
			int get();
			void set(int value);
		}

		property Vector3Array^ VertexBase
		{
			Vector3Array^ get();
			void set(Vector3Array^ value);
		}

		property int VertexStride
		{
			int get();
			void set(int value);
		}

		property PhyScalarType VertexType
		{
			PhyScalarType get();
			void set(PhyScalarType value);
		}

	internal:
		property btIndexedMesh* UnmanagedPointer
		{
			virtual btIndexedMesh* get();
			void set(btIndexedMesh* value);
		}
	};

	public ref class TriangleIndexVertexArray : StridingMeshInterface
	{
	internal:
		TriangleIndexVertexArray(btTriangleIndexVertexArray* vertexArray);

	public:
		TriangleIndexVertexArray();
		TriangleIndexVertexArray(int numTriangles, IntPtr triangleIndexBase, int triangleIndexStride,
			int numVertices, IntPtr vertexBase, int vertexStride);
		TriangleIndexVertexArray(array<int>^ indices, array<Vector3>^ vertices);
		TriangleIndexVertexArray(array<int>^ indices, array<btScalar>^ vertices);

		void AddIndexedMesh(IndexedMesh^ mesh);
		void AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType);

		property AlignedIndexedMeshArray^ IndexedMeshArray
		{
			AlignedIndexedMeshArray^ get();
		}

	internal:
		property btTriangleIndexVertexArray* UnmanagedPointer
		{
			btTriangleIndexVertexArray* get();
		}
	};
};
