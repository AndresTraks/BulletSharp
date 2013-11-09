#include "StdAfx.h"

#include "TriangleMesh.h"

#define Native static_cast<btTriangleMesh*>(_native)

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
	Native->addIndex(index);
}

int TriangleMesh::FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices)
{
	VECTOR3_DEF(vertex);
	int ret = Native->findOrAddVertex(VECTOR3_USE(vertex), removeDuplicateVertices);
	VECTOR3_DEL(vertex);
	return ret;
}
#endif

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices)
{
	VECTOR3_DEF(vertex0);
	VECTOR3_DEF(vertex1);
	VECTOR3_DEF(vertex2);

	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2), removeDuplicateVertices);
	
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2)
{
	VECTOR3_DEF(vertex0);
	VECTOR3_DEF(vertex1);
	VECTOR3_DEF(vertex2);

	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2));
	
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::PreallocateIndexes(int indexCount)
{
	Native->preallocateIndices(indexCount);
}

int TriangleMesh::TriangleCount::get()
{
	return Native->getNumTriangles();
}

int TriangleMesh::Use32BitIndexes::get()
{
	return Native->getUse32bitIndices();
}

int TriangleMesh::Use4ComponentVertices::get()
{
	return Native->getUse4componentVertices();
}

btScalar TriangleMesh::WeldingThreshold::get()
{
	return Native->m_weldingThreshold;
}

void TriangleMesh::WeldingThreshold::set(btScalar value)
{
	Native->m_weldingThreshold = value;
}
