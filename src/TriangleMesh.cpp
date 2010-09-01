#include "StdAfx.h"

#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(btTriangleMesh* mesh)
: TriangleIndexVertexArray(mesh)
{
}

TriangleMesh::TriangleMesh(bool use32bitIndices, bool use4componentVertices)
: TriangleIndexVertexArray(new btTriangleMesh(use32bitIndices, use4componentVertices))
{
}

TriangleMesh::TriangleMesh(bool use32bitIndices)
: TriangleIndexVertexArray(new btTriangleMesh(use32bitIndices))
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
	btVector3* vertexTemp = Math::Vector3ToBtVector3(vertex);
	int ret = UnmanagedPointer->findOrAddVertex(*vertexTemp, removeDuplicateVertices);

	delete vertexTemp;
	return ret;
}
#endif

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, bool removeDuplicateVertices)
{
	btVector3* vertex0Temp = Math::Vector3ToBtVector3(vertex0);
	btVector3* vertex1Temp = Math::Vector3ToBtVector3(vertex1);
	btVector3* vertex2Temp = Math::Vector3ToBtVector3(vertex2);

	UnmanagedPointer->addTriangle(*vertex0Temp, *vertex1Temp, *vertex2Temp, removeDuplicateVertices);
	
	delete vertex0Temp;
	delete vertex1Temp;
	delete vertex2Temp;
}

void TriangleMesh::AddTriangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2)
{
	btVector3* vertex0Temp = Math::Vector3ToBtVector3(vertex0);
	btVector3* vertex1Temp = Math::Vector3ToBtVector3(vertex1);
	btVector3* vertex2Temp = Math::Vector3ToBtVector3(vertex2);

	UnmanagedPointer->addTriangle(*vertex0Temp, *vertex1Temp, *vertex2Temp);
	
	delete vertex0Temp;
	delete vertex1Temp;
	delete vertex2Temp;
}

void TriangleMesh::PreallocateIndices(int numIndices)
{
	UnmanagedPointer->preallocateIndices(numIndices);
}

void TriangleMesh::PreallocateVertices(int numVertices)
{
	UnmanagedPointer->preallocateVertices(numVertices);
}

int TriangleMesh::NumTriangles::get()
{
	return UnmanagedPointer->getNumTriangles();
}

int TriangleMesh::Use32bitIndices::get()
{
	return UnmanagedPointer->getUse32bitIndices();
}

int TriangleMesh::Use4componentVertices::get()
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
