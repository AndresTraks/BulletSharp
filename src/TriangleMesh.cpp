#include "StdAfx.h"

#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(btTriangleMesh* mesh)
: TriangleIndexVertexArray(mesh)
{
}

TriangleMesh::TriangleMesh(bool use32BitIndexes, bool use4ComponentVertices)
: TriangleIndexVertexArray(new btTriangleMesh(use32BitIndexes, use4ComponentVertices))
{
}

TriangleMesh::TriangleMesh(bool use32BitIndexes)
: TriangleIndexVertexArray(new btTriangleMesh(use32BitIndexes))
{
}

TriangleMesh::TriangleMesh()
: TriangleIndexVertexArray(new btTriangleMesh())
{
}

#ifndef DISABLE_INTERNAL
void TriangleMesh::AddIndex(int index)
{
	UnmanagedPointer->addIndex(index);
}

int TriangleMesh::FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices)
{
	VECTOR3_DEF(vertex);
	int ret = UnmanagedPointer->findOrAddVertex(VECTOR3_USE(vertex), removeDuplicateVertices);
	VECTOR3_DEL(vertex);
	return ret;
}
#endif

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices)
{
	VECTOR3_DEF(vertex0);
	VECTOR3_DEF(vertex1);
	VECTOR3_DEF(vertex2);

	UnmanagedPointer->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2), removeDuplicateVertices);
	
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2)
{
	VECTOR3_DEF(vertex0);
	VECTOR3_DEF(vertex1);
	VECTOR3_DEF(vertex2);

	UnmanagedPointer->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2));
	
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::PreallocateIndexes(int indexCount)
{
	UnmanagedPointer->preallocateIndices(indexCount);
}

void TriangleMesh::PreallocateVertices(int vertexCount)
{
	UnmanagedPointer->preallocateVertices(vertexCount);
}

int TriangleMesh::TriangleCount::get()
{
	return UnmanagedPointer->getNumTriangles();
}

int TriangleMesh::Use32BitIndexes::get()
{
	return UnmanagedPointer->getUse32bitIndices();
}

int TriangleMesh::Use4ComponentVertices::get()
{
	return UnmanagedPointer->getUse4componentVertices();
}

btScalar TriangleMesh::WeldingThreshold::get()
{
	return UnmanagedPointer->m_weldingThreshold;
}

void TriangleMesh::WeldingThreshold::set(btScalar value)
{
	UnmanagedPointer->m_weldingThreshold = value;
}

btTriangleMesh* TriangleMesh::UnmanagedPointer::get()
{
	return (btTriangleMesh*)TriangleIndexVertexArray::UnmanagedPointer;
}
