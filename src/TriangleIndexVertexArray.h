#pragma once

#include "StridingMeshInterface.h"

namespace BulletSharp
{
	ref class AlignedIndexedMeshArray;
	ref class DataStream;
	ref class IntArray;
	ref class Vector3Array;

	public ref class IndexedMesh
	{
	internal:
		btIndexedMesh* _native;

	private:
		bool _preventDelete;
		bool _ownsData;
		IntArray^ _triangleIndices;
		Vector3Array^ _vertices;

	internal:
		IndexedMesh(btIndexedMesh* native, bool preventDelete);

		~IndexedMesh();
		!IndexedMesh();

	public:
		IndexedMesh();

		void Allocate(int numTriangles, int numVertices, int triangleIndexStride, int vertexStride,
			PhyScalarType indexType, PhyScalarType vertexType);
		void Free();
		DataStream^ LockIndices();
		DataStream^ LockVerts();

		property PhyScalarType IndexType
		{
			PhyScalarType get();
			//The index type is set when adding an indexed mesh to the
			// btTriangleIndexVertexArray, do not set it manually
			//void set(PhyScalarType value);
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
	private:
		AlignedIndexedMeshArray^ _indexedMeshArray;
		IndexedMesh^ _initialMesh;
		List<IndexedMesh^>^ _meshes;

	internal:
		TriangleIndexVertexArray(btTriangleIndexVertexArray* native);

		!TriangleIndexVertexArray();
		~TriangleIndexVertexArray();

	public:
		TriangleIndexVertexArray(int numTriangles, IntPtr triangleIndexBase, int triangleIndexStride,
			int numVertices, IntPtr vertexBase, int vertexStride);
		TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<Vector3>^ vertices);
		TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<float>^ vertices);
		TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<double>^ vertices);
		TriangleIndexVertexArray();

		void AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType);
		void AddIndexedMesh(IndexedMesh^ mesh);

		property AlignedIndexedMeshArray^ IndexedMeshArray
		{
			AlignedIndexedMeshArray^ get();
		}
	};
};
