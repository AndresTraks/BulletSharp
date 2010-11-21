#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "DataStream.h"
#include "TriangleIndexVertexArray.h"

IndexedMesh::IndexedMesh(btIndexedMesh* indexedMesh)
{
	_indexedMesh = indexedMesh;
}

IndexedMesh::IndexedMesh()
{
	_indexedMesh = new btIndexedMesh();
}

void IndexedMesh::Allocate(int numVerts, int vertexStride, int numIndices, int indexStride)
{
	AllocateVerts(numVerts, vertexStride);
	AllocateIndices(numIndices, indexStride);
}

void IndexedMesh::AllocateVerts(int num, int stride)
{
	_indexedMesh->m_numVertices = num;
	_indexedMesh->m_vertexStride = stride;
	//_indexedMesh->m_indexType = PHY_INTEGER;

	_indexedMesh->m_vertexBase = (const unsigned char *)new btVector3[num];
}

void IndexedMesh::AllocateIndices(int num, int stride)
{
	_indexedMesh->m_numTriangles = num;
	_indexedMesh->m_triangleIndexStride = stride;
	//_IndexedMesh->m_vertexType = PHY_FLOAT;

	_indexedMesh->m_triangleIndexBase = (const unsigned char *)new int[num*3];
}

BulletSharp::DataStream^ IndexedMesh::LockVerts()
{
	return gcnew DataStream((void*)_indexedMesh->m_vertexBase,
		_indexedMesh->m_numVertices * _indexedMesh->m_vertexStride, true, true, false);
}

BulletSharp::DataStream^ IndexedMesh::LockIndices()
{
	return gcnew DataStream((void*)_indexedMesh->m_triangleIndexBase,
		_indexedMesh->m_numTriangles * _indexedMesh->m_triangleIndexStride, true, true, false);
}

PhyScalarType IndexedMesh::IndexType::get()
{
	return (PhyScalarType)_indexedMesh->m_indexType;
}
void IndexedMesh::IndexType::set(PhyScalarType value)
{
	_indexedMesh->m_indexType = (PHY_ScalarType)value;
}

int IndexedMesh::NumTriangles::get()
{
	return _indexedMesh->m_numTriangles;
}
void IndexedMesh::NumTriangles::set(int value)
{
	_indexedMesh->m_numTriangles = value;
}

int IndexedMesh::NumVertices::get()
{
	return _indexedMesh->m_numVertices;
}
void IndexedMesh::NumVertices::set(int value)
{
	_indexedMesh->m_numVertices = value;
}

IntArray^ IndexedMesh::TriangleIndexBase::get()
{
	return gcnew IntArray((int*)_indexedMesh->m_triangleIndexBase, _indexedMesh->m_numTriangles * _indexedMesh->m_triangleIndexStride / sizeof(int));
}
void IndexedMesh::TriangleIndexBase::set(IntArray^ value)
{
	_indexedMesh->m_triangleIndexBase = (unsigned char*)value->UnmanagedPointer;
}

int IndexedMesh::TriangleIndexStride::get()
{
	return _indexedMesh->m_triangleIndexStride;
}
void IndexedMesh::TriangleIndexStride::set(int value)
{
	_indexedMesh->m_triangleIndexStride = value;
}

Vector3Array^ IndexedMesh::VertexBase::get()
{
	return gcnew Vector3Array((btVector3*)_indexedMesh->m_vertexBase, _indexedMesh->m_numVertices);
}
void IndexedMesh::VertexBase::set(Vector3Array^ value)
{
	_indexedMesh->m_vertexBase = (unsigned char*)value->UnmanagedPointer;
}

int IndexedMesh::VertexStride::get()
{
	return _indexedMesh->m_vertexStride;
}
void IndexedMesh::VertexStride::set(int value)
{
	_indexedMesh->m_vertexStride = value;
}

PhyScalarType IndexedMesh::VertexType::get()
{
	return (PhyScalarType)_indexedMesh->m_vertexType;
}
void IndexedMesh::VertexType::set(PhyScalarType value)
{
	_indexedMesh->m_vertexType = (PHY_ScalarType)value;
}

btIndexedMesh* IndexedMesh::UnmanagedPointer::get()
{
	return _indexedMesh;
}
void IndexedMesh::UnmanagedPointer::set(btIndexedMesh* value)
{
	_indexedMesh = value;
}


TriangleIndexVertexArray::TriangleIndexVertexArray(btTriangleIndexVertexArray* vertexArray)
: StridingMeshInterface(vertexArray)
{
}

TriangleIndexVertexArray::TriangleIndexVertexArray()
: StridingMeshInterface(new btTriangleIndexVertexArray())
{
}

TriangleIndexVertexArray::TriangleIndexVertexArray(int numTriangles, IntPtr triangleIndexBase, int triangleIndexStride,
	int numVertices, IntPtr vertexBase, int vertexStride)
: StridingMeshInterface(new btTriangleIndexVertexArray(numTriangles, (int*)triangleIndexBase.ToPointer(), triangleIndexStride,
	numVertices, (btScalar*)vertexBase.ToPointer(), vertexStride))
{
}

TriangleIndexVertexArray::TriangleIndexVertexArray(array<int>^ indices, array<Vector3>^ vertices)
: StridingMeshInterface(0)
{
	pin_ptr<int> indicesPtr = &indices[0];
	int* indicesBase = new int[indices->Length];
	btVector3* verticesBase = Math::Vector3ArrayToUnmanaged(vertices);

	memcpy(indicesBase, indicesPtr, indices->Length * sizeof(int));

	UnmanagedPointer = new btTriangleIndexVertexArray(indices->Length / 3, indicesBase, 3 * sizeof(int),
		vertices->Length, *verticesBase, sizeof(btVector3));
}

TriangleIndexVertexArray::TriangleIndexVertexArray(array<int>^ indices, array<btScalar>^ vertices)
: StridingMeshInterface(0)
{
	pin_ptr<int> indicesPtr = &indices[0];
	pin_ptr<btScalar> verticesPtr = &vertices[0];
	int* indicesBase = new int[indices->Length];
	btScalar* verticesBase = new btScalar[vertices->Length];

	memcpy(indicesBase, indicesPtr, indices->Length * sizeof(int));
	memcpy(verticesBase, verticesPtr, vertices->Length * sizeof(btScalar));

	UnmanagedPointer = new btTriangleIndexVertexArray(indices->Length / 3, indicesBase, 3 * sizeof(int),
		vertices->Length / 3, verticesBase, 3 * sizeof(btScalar));
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh)
{
	UnmanagedPointer->addIndexedMesh(*mesh->UnmanagedPointer);
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType)
{
	UnmanagedPointer->addIndexedMesh(*mesh->UnmanagedPointer, static_cast<PHY_ScalarType>(indexType));
}

AlignedIndexedMeshArray^ TriangleIndexVertexArray::IndexedMeshArray::get()
{
	return gcnew AlignedIndexedMeshArray(&UnmanagedPointer->getIndexedMeshArray());
}

btTriangleIndexVertexArray* TriangleIndexVertexArray::UnmanagedPointer::get()
{
	return (btTriangleIndexVertexArray*)StridingMeshInterface::UnmanagedPointer;
}