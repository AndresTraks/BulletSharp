#include "StdAfx.h"

#include "DataStream.h"
#include "TriangleIndexVertexMaterialArray.h"

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(btTriangleIndexVertexMaterialArray* triangleArray)
: TriangleIndexVertexArray(triangleArray)
{
}

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray()
: TriangleIndexVertexArray(new btTriangleIndexVertexMaterialArray())
{
}

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(int numTriangles, IntPtr triangleIndexBase,
	int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride, int numMaterials,
	IntPtr materialBase, int materialStride, IntPtr triangleMaterialsBase, int materialIndexStride)
: TriangleIndexVertexArray(new btTriangleIndexVertexMaterialArray(numTriangles, (int*)triangleIndexBase.ToPointer(),
	triangleIndexStride, numVertices, (btScalar*)vertexBase.ToPointer(), vertexStride, numMaterials,
	(unsigned char*)materialBase.ToPointer(), materialStride, (int*)triangleMaterialsBase.ToPointer(), materialIndexStride))
{
}
