#pragma once

#include "Enums.h"
#include "StridingMeshInterface.h"

namespace BulletSharp
{
	ref class AlignedObjectArray;
	ref class DataStream;

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
		}

		property int NumVertices
		{
			int get();
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


	public ref class BtIndexedMeshArray : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btAlignedObjectArray<btIndexedMesh>* _alignedObjectArray;

	internal:
		BtIndexedMeshArray(IndexedMeshArray* indexedMeshArray)
		{
			_alignedObjectArray = indexedMeshArray;
		}

	public:
		BtIndexedMeshArray()
		{
			_alignedObjectArray = new btAlignedObjectArray<btIndexedMesh>();
		}
		
		!BtIndexedMeshArray()
		{
			if( this->IsDisposed == true )
				return;

			OnDisposing( this, nullptr );

			_alignedObjectArray = NULL;

			OnDisposed( this, nullptr );
		}

	protected:
		~BtIndexedMeshArray()
		{
			this->!BtIndexedMeshArray();
		}

	public:
		property bool IsDisposed
		{
			virtual bool get()
			{
				return (_alignedObjectArray == NULL);
			}
		}

		void Clear()
		{
			_alignedObjectArray->clear();
		}

		void PopBack()
		{
			_alignedObjectArray->pop_back();
		}

		void PushBack(IndexedMesh^ indexedMesh)
		{
			_alignedObjectArray->push_back(*indexedMesh->UnmanagedPointer);
		}

		property int Size
		{
			int get()
			{
				return _alignedObjectArray->size();
			}
		}

		property int Capacity
		{
			int get()
			{
				return _alignedObjectArray->capacity();
			}
		}

		property IndexedMesh^ default [int]
		{
			IndexedMesh^ get (int index)
			{
				if (index >= Capacity)
					return nullptr;

				btIndexedMesh* obj = &((*_alignedObjectArray)[index]);
				if (obj != nullptr)
					return gcnew IndexedMesh(obj);
				else
					return nullptr;
			}
		}

	internal:
		property btAlignedObjectArray<btIndexedMesh>* UnmanagedPointer
		{
			virtual btAlignedObjectArray<btIndexedMesh>* get()
			{
				return _alignedObjectArray;
			}
			void set( btAlignedObjectArray<btIndexedMesh>* value )
			{
				_alignedObjectArray = value;
			}
		}
	};


	public ref class TriangleIndexVertexArray : StridingMeshInterface
	{
	internal:
		TriangleIndexVertexArray(btTriangleIndexVertexArray* vertexArray);
	
	public:
		TriangleIndexVertexArray();

		void AddIndexedMesh(IndexedMesh^ mesh);
		void AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType);

		property BtIndexedMeshArray^ IndexedMeshArray
		{
			BtIndexedMeshArray^ get();
		}

	internal:
		property btTriangleIndexVertexArray* UnmanagedPointer
		{
			btTriangleIndexVertexArray* get();
		}
	};
};
