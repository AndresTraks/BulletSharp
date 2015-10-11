#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "DataStream.h"
#include "TriangleIndexVertexArray.h"

IndexedMesh::IndexedMesh(btIndexedMesh* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

IndexedMesh::~IndexedMesh()
{
	this->!IndexedMesh();
}

IndexedMesh::!IndexedMesh()
{
	if (_native)
	{
		Free();
		if (!_preventDelete)
		{
			delete _native;
		}
		_native = NULL;
	}
}

IndexedMesh::IndexedMesh()
{
	_native = new btIndexedMesh();
}

void IndexedMesh::Allocate(int numTriangles, int numVertices, int triangleIndexStride, int vertexStride,
	PhyScalarType indexType, PhyScalarType vertexType)
{
	if (_ownsData)
	{
		Free();
	}
	else
	{
		_ownsData = true;
	}

	_native->m_numVertices = numVertices;
	_native->m_vertexStride = vertexStride;
	_native->m_vertexType = (PHY_ScalarType)vertexType;
	_native->m_vertexBase = new unsigned char[numVertices * vertexStride];

	_native->m_numTriangles = numTriangles;
	_native->m_triangleIndexStride = triangleIndexStride;
	_native->m_indexType = (PHY_ScalarType)indexType;
	_native->m_triangleIndexBase = new unsigned char[numTriangles * triangleIndexStride];
}

void IndexedMesh::Free()
{
	if (_ownsData)
	{
		delete[] _native->m_vertexBase;
		delete[] _native->m_triangleIndexBase;
		_native->m_vertexBase = 0;
		_native->m_triangleIndexBase = 0;
		_ownsData = false;
	}
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
/*
void IndexedMesh::IndexType::set(PhyScalarType value)
{
	_native->m_indexType = (PHY_ScalarType)value;
}
*/

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

IntPtr IndexedMesh::TriangleIndexBase::get()
{
	return IntPtr((void*)_native->m_triangleIndexBase);
}
void IndexedMesh::TriangleIndexBase::set(IntPtr value)
{
	_native->m_triangleIndexBase = (unsigned char*)value.ToPointer();
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
	_vertices->Stride = VertexStride;
	return _vertices;
}
void IndexedMesh::Vertices::set(Vector3Array^ value)
{
	_native->m_vertexBase = (unsigned char*)value->_native;
	_vertices = value;
}

IntPtr IndexedMesh::VertexBase::get()
{
	return IntPtr((void*)_native->m_vertexBase);
}
void IndexedMesh::VertexBase::set(IntPtr value)
{
	_native->m_vertexBase = (unsigned char*)value.ToPointer();
}

int IndexedMesh::VertexStride::get()
{
	return _native->m_vertexStride;
}
void IndexedMesh::VertexStride::set(int value)
{
	_native->m_vertexStride = value;

	if (_vertices != nullptr)
	{
		_vertices->Stride = value;
	}
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

TriangleIndexVertexArray::TriangleIndexVertexArray(btTriangleIndexVertexArray* native)
	: StridingMeshInterface(native)
{
	_meshes = gcnew List<IndexedMesh^>();
}

TriangleIndexVertexArray::~TriangleIndexVertexArray()
{
	this->!TriangleIndexVertexArray();
}

TriangleIndexVertexArray::!TriangleIndexVertexArray()
{
	if (_initialMesh)
	{
		delete _initialMesh;
		_initialMesh = nullptr;
	}
}

TriangleIndexVertexArray::TriangleIndexVertexArray(int numTriangles, IntPtr triangleIndexBase,
	int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride)
	: StridingMeshInterface(new btTriangleIndexVertexArray(numTriangles, (int*)triangleIndexBase.ToPointer(),
		triangleIndexStride, numVertices, (btScalar*)vertexBase.ToPointer(), vertexStride))
{
	_meshes = gcnew List<IndexedMesh^>();
}

TriangleIndexVertexArray::TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<Vector3>^ vertices)
: StridingMeshInterface(new btTriangleIndexVertexArray())
{
	_initialMesh = gcnew IndexedMesh();
	_initialMesh->Allocate(indices->Count / 3, vertices->Count, sizeof(int) * 3, sizeof(float) * 3,
		PhyScalarType::Int32, PhyScalarType::Single);

	array<int>^ indexArray = dynamic_cast<array<int>^>(indices);
	if (!indexArray)
	{
		indexArray = gcnew array<int>(indices->Count);
		indices->CopyTo(indexArray, 0);
	}
	Marshal::Copy(indexArray, 0, _initialMesh->TriangleIndexBase, indices->Count);

	array<float>^ vertexArray = gcnew array<float>(vertices->Count * 3);
	int i = 0;
	for each (Vector3 v in vertices)
	{
		vertexArray[i] = Vector_X(v);
		vertexArray[i + 1] = Vector_Y(v);
		vertexArray[i + 2] = Vector_Z(v);
		i += 3;
	}
	Marshal::Copy(vertexArray, 0, _initialMesh->VertexBase, vertexArray->Length);

	_meshes = gcnew List<IndexedMesh^>();
	AddIndexedMesh(_initialMesh);
}

TriangleIndexVertexArray::TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<float>^ vertices)
: StridingMeshInterface(new btTriangleIndexVertexArray())
{
	_initialMesh = gcnew IndexedMesh();
	_initialMesh->Allocate(indices->Count / 3, vertices->Count / 3, sizeof(int) * 3, sizeof(float) * 3,
		PhyScalarType::Int32, PhyScalarType::Single);

	array<int>^ indexArray = dynamic_cast<array<int>^>(indices);
	if (!indexArray)
	{
		indexArray = gcnew array<int>(indices->Count);
		indices->CopyTo(indexArray, 0);
	}
	Marshal::Copy(indexArray, 0, _initialMesh->TriangleIndexBase, indexArray->Length);

	array<float>^ vertexArray = dynamic_cast<array<float>^>(vertices);
	if (!vertexArray)
	{
		vertexArray = gcnew array<float>(vertices->Count);
		vertices->CopyTo(vertexArray, 0);
	}
	Marshal::Copy(vertexArray, 0, _initialMesh->VertexBase, vertexArray->Length);

	_meshes = gcnew List<IndexedMesh^>();
	AddIndexedMesh(_initialMesh);
}

TriangleIndexVertexArray::TriangleIndexVertexArray(ICollection<int>^ indices, ICollection<double>^ vertices)
: StridingMeshInterface(new btTriangleIndexVertexArray())
{
	_initialMesh = gcnew IndexedMesh();
	_initialMesh->Allocate(indices->Count / 3, vertices->Count / 3, sizeof(int) * 3, sizeof(double) * 3,
		PhyScalarType::Int32, PhyScalarType::Double);

	array<int>^ indexArray = dynamic_cast<array<int>^>(indices);
	if (!indexArray)
	{
		indexArray = gcnew array<int>(indices->Count);
		indices->CopyTo(indexArray, 0);
	}
	Marshal::Copy(indexArray, 0, _initialMesh->TriangleIndexBase, indexArray->Length);

	array<double>^ vertexArray = dynamic_cast<array<double>^>(vertices);
	if (!vertexArray)
	{
		vertexArray = gcnew array<double>(vertices->Count);
		vertices->CopyTo(vertexArray, 0);
	}
	Marshal::Copy(vertexArray, 0, _initialMesh->VertexBase, vertexArray->Length);

	_meshes = gcnew List<IndexedMesh^>();
	AddIndexedMesh(_initialMesh);
}

TriangleIndexVertexArray::TriangleIndexVertexArray()
	: StridingMeshInterface(new btTriangleIndexVertexArray())
{
	_meshes = gcnew List<IndexedMesh^>();
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh, PhyScalarType indexType)
{
	Native->addIndexedMesh(*mesh->_native, (PHY_ScalarType)indexType);
	_meshes->Add(mesh);
}

void TriangleIndexVertexArray::AddIndexedMesh(IndexedMesh^ mesh)
{
	Native->addIndexedMesh(*mesh->_native);
	_meshes->Add(mesh);
}

AlignedIndexedMeshArray^ TriangleIndexVertexArray::IndexedMeshArray::get()
{
	// _indexedMeshArray is not the same as _meshes,
	// btTriangleIndexVertexArray stores it's own copy of the btIndexedMesh structures.
	if (_indexedMeshArray == nullptr)
	{
		_indexedMeshArray = gcnew AlignedIndexedMeshArray(&Native->getIndexedMeshArray());
	}
	return _indexedMeshArray;
}
