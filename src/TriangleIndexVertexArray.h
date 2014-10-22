#pragma once

#include "StridingMeshInterface.h"

namespace BulletSharp
{
	ref class AlignedIndexedMeshArray;
	ref class DataStream;
	ref class IntArray;
	ref class Vector3Array;

	public ref class IndexedMesh : IDisposable
	{
	internal:
		btIndexedMesh* _native;

	private:
		bool _preventDelete;
		IntArray^ _triangleIndices;
		Vector3Array^ _vertices;

	internal:
		IndexedMesh(btIndexedMesh* native, bool preventDelete);

	public:
		!IndexedMesh();
	protected:
		~IndexedMesh();

	public:
		IndexedMesh();

		void Allocate(int numVertices, int vertexStride, int numTriangles, int triangleIndexStride);
		DataStream^ LockIndices();
		DataStream^ LockVerts();

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

		property IntArray^ TriangleIndices
		{
			IntArray^ get();
			void set(IntArray^ value);
		}

		property IntPtr TriangleIndexBase
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int TriangleIndexStride
		{
			int get();
			void set(int value);
		}

		property IntPtr VertexBase
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property Vector3Array^ Vertices
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
	};

	public ref class TriangleIndexVertexArray : StridingMeshInterface
	{
	internal:
		TriangleIndexVertexArray(btTriangleIndexVertexArray* native);

	private:
		AlignedIndexedMeshArray^ _indexedMeshArray;
		System::Collections::Generic::List<IndexedMesh^>^ _meshes;

	public:
		TriangleIndexVertexArray(int numTriangles, IntPtr triangleIndexBase, int triangleIndexStride,
			int numVertices, IntPtr vertexBase, int vertexStride);
		TriangleIndexVertexArray(array<int>^ indices, array<Vector3>^ vertices);
		TriangleIndexVertexArray(array<int>^ indices, array<btScalar>^ vertices);
		TriangleIndexVertexArray();

		void AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType);
		void AddIndexedMesh(IndexedMesh^ mesh);

		property AlignedIndexedMeshArray^ IndexedMeshArray
		{
			AlignedIndexedMeshArray^ get();
		}
	};
};
