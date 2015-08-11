#include "StdAfx.h"

#include "TriangleMesh.h"

#define Native static_cast<btTriangleMesh*>(_native)

TriangleMesh::TriangleMesh(btTriangleMesh* native)
	: TriangleIndexVertexArray(native)
{
}

TriangleMesh::TriangleMesh(bool use32BitIndices, bool use4ComponentVertices)
	: TriangleIndexVertexArray(new btTriangleMesh(use32BitIndices, use4ComponentVertices))
{
}

TriangleMesh::TriangleMesh(bool use32BitIndices)
	: TriangleIndexVertexArray(new btTriangleMesh(use32BitIndices))
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
#endif

void TriangleMesh::AddTriangleRef(Vector3% vertex0, Vector3% vertex1, Vector3% vertex2,
	bool removeDuplicateVertices)
{
	VECTOR3_CONV(vertex0);
	VECTOR3_CONV(vertex1);
	VECTOR3_CONV(vertex2);
	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2),
		removeDuplicateVertices);
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2,
	bool removeDuplicateVertices)
{
	VECTOR3_CONV(vertex0);
	VECTOR3_CONV(vertex1);
	VECTOR3_CONV(vertex2);
	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2),
		removeDuplicateVertices);
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangleRef(Vector3% vertex0, Vector3% vertex1, Vector3% vertex2)
{
	VECTOR3_CONV(vertex0);
	VECTOR3_CONV(vertex1);
	VECTOR3_CONV(vertex2);
	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2));
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2)
{
	VECTOR3_CONV(vertex0);
	VECTOR3_CONV(vertex1);
	VECTOR3_CONV(vertex2);
	Native->addTriangle(VECTOR3_USE(vertex0), VECTOR3_USE(vertex1), VECTOR3_USE(vertex2));
	VECTOR3_DEL(vertex0);
	VECTOR3_DEL(vertex1);
	VECTOR3_DEL(vertex2);
}

void TriangleMesh::AddTriangleIndices(int index1, int index2, int index3)
{
	Native->addTriangleIndices(index1, index2, index3);
}

#ifndef DISABLE_INTERNAL
int TriangleMesh::FindOrAddVertex(Vector3 vertex, bool removeDuplicateVertices)
{
	VECTOR3_CONV(vertex);
	int ret = Native->findOrAddVertex(VECTOR3_USE(vertex), removeDuplicateVertices);
	VECTOR3_DEL(vertex);
	return ret;
}
#endif

int TriangleMesh::NumTriangles::get()
{
	return Native->getNumTriangles();
}

bool TriangleMesh::Use32BitIndices::get()
{
	return Native->getUse32bitIndices();
}

bool TriangleMesh::Use4ComponentVertices::get()
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
