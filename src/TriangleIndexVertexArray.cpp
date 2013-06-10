#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "DataStream.h"
#include "TriangleIndexVertexArray.h"

IndexedMesh::IndexedMesh(btIndexedMesh* indexedMesh)
{
	_native = indexedMesh;
}

IndexedMesh::IndexedMesh()
{
	_native = new btIndexedMesh();
}

void IndexedMesh::Allocate(int numVerts, int vertexStride, int numIndices, int indexStride)
{
	AllocateVerts(numVerts, vertexStride);
	AllocateIndices(numIndices, indexStride);
}

void IndexedMesh::AllocateVerts(int num, int stride)
{
	_native->m_numVertices = num;
	_native->m_vertexStride = stride;
	//_native->m_indexType = PHY_INTEGER;

	_native->m_vertexBase = (const unsigned char *)new btVector3[num];
}

void IndexedMesh::AllocateIndices(int num, int stride)
{
	_native->m_numTriangles = num;
	_native->m_triangleIndexStride = stride;
	//_native->m_vertexType = PHY_FLOAT;

	_native->m_triangleIndexBase = (const unsigned char *)new int[num*3];
}

BulletSharp::DataStream^ IndexedMesh::LockIndices()
{
	return gcnew DataStream((void*)_native->m_triangleIndexBase,
		_native->m_numTriangles * _native->m_triangleIndexStride, true, true, false);
}

BulletSharp::DataStream^ IndexedMesh::LockVerts()
{
	return gcnew DataStream((void*)_native->m_vertexBase,
		_native->m_numVertices * _native->m_vertexStride, true, true, false);
}

PhyScalarType IndexedMesh::IndexType::get()
{
	return (PhyScalarType)_native->m_indexType;
}
void IndexedMesh::IndexType::set(PhyScalarType value)
{
	_native->m_indexType = (PHY_ScalarType)value;
}

int IndexedMesh::NumTriangles::get()
{
	return _native->m_numTriangles;
}
void IndexedMesh::NumTriangles::set(int value)
{
	_native->m_numTriangles = value;
}

int IndexedMesh::NumVertices::get()
{
	return _native->m_numVertices;
}
void IndexedMesh::NumVertices::set(int value)
{
	_native->m_numVertices = value;
}

IntArray^ IndexedMesh::TriangleIndices::get()
{
	int count = _native->m_numTriangles * _native->m_triangleIndexStride / sizeof(int);
	int* triangleIndexBase = (int*)_native->m_triangleIndexBase;

	if (_triangleIndices != nullptr &&
		(int*)_triangleIndices->_native == triangleIndexBase &&
		_triangleIndices->Count == count)
	{
		return _triangleIndices;
	}

	_triangleIndices = gcnew IntArray(triangleIndexBase, count);
	return _triangleIndices;
}
void IndexedMesh::TriangleIndices::set(IntArray^ value)
{
	_native->m_triangleIndexBase = (unsigned char*)value->_native;
	_triangleIndices = value;
}

int IndexedMesh::TriangleIndexStride::get()
{
	return _native->m_triangleIndexStride;
}
void IndexedMesh::TriangleIndexStride::set(int value)
{
	_native->m_triangleIndexStride = value;
}

Vector3Array^ IndexedMesh::Vertices::get()
{
	int count = _native->m_numVertices;
	btVector3* vertexBase = (btVector3*)_native->m_vertexBase;

	if (_vertices != nullptr &&
		(btVector3*)_vertices->_native == vertexBase &&
		_vertices->Count == count)
	{
		return _vertices;
	}

	_vertices = gcnew Vector3Array(vertexBase, count);
	return _vertices;
}
void IndexedMesh::Vertices::set(Vector3Array^ value)
{
	_native->m_vertexBase = (unsigned char*)value->_native;
	_vertices = value;
}

int IndexedMesh::VertexStride::get()
{
	return _native->m_vertexStride;
}
void IndexedMesh::VertexStride::set(int value)
{
	_native->m_vertexStride = value;
}

PhyScalarType IndexedMesh::VertexType::get()
{
	return (PhyScalarType)_native->m_vertexType;
}
void IndexedMesh::VertexType::set(PhyScalarType value)
{
	_native->m_vertexType = (PHY_ScalarType)value;
}


#define Native static_cast<btTriangleIndexVertexArray*>(_native)

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
	int* indicesBase = Math::IntArrayToUnmanaged(indices);
	btVector3* verticesBase = Math::Vector3ArrayToUnmanaged(vertices);

	_native = new btTriangleIndexVertexArray(indices->Length / 3, indicesBase, 3 * sizeof(int),
		vertices->Length, *verticesBase, sizeof(btVector3));
}

TriangleIndexVertexArray::TriangleIndexVertexArray(array<int>^ indices, array<btScalar>^ vertices)
: StridingMeshInterface(0)
{
	int* indicesBase = Math::IntArrayToUnmanaged(indices);
	btScalar* verticesBase = Math::BtScalarArrayToUnmanaged(vertices);

	_native = new btTriangleIndexVertexArray(indices->Length / 3, indicesBase, 3 * sizeof(int),
		vertices->Length / 3, verticesBase, 3 * sizeof(btScalar));
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh)
{
	Native->addIndexedMesh(*mesh->_native);
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType)
{
	Native->addIndexedMesh(*mesh->_native, static_cast<PHY_ScalarType>(indexType));
}

AlignedIndexedMeshArray^ TriangleIndexVertexArray::IndexedMeshArray::get()
{
	return gcnew AlignedIndexedMeshArray(&Native->getIndexedMeshArray());
}
