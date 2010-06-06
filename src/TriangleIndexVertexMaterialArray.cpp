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

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(array<int>^ indices, array<Vector3>^ vertices,
	array<BulletMaterial>^ materials, array<int>^ materialIndices)
: TriangleIndexVertexArray(0)
{
	// Indices
	pin_ptr<int> indicesBase = &indices[0];
	int* indicesArray = new int[indices->Length];
	memcpy(indicesArray, indicesBase, indices->Length * sizeof(int));

	// Vertices
	btVector3* verticesArray = new btVector3[vertices->Length];
	for(int i=0; i<vertices->Length; i++)
		Math::Vector3ToBtVector3(vertices[i], &verticesArray[i]);

	// Materials
	pin_ptr<BulletMaterial> materialsBase = &materials[0];
	unsigned char* materialsArray = new unsigned char[materials->Length * BulletMaterial::SizeInBytes];
	memcpy(materialsArray, (unsigned char*)materialsBase, materials->Length * BulletMaterial::SizeInBytes);

	// Material indices
	pin_ptr<int> materialIndicesBase = &materialIndices[0];
	int* materialIndicesArray = new int[indices->Length / 3];
	memcpy(materialIndicesArray, materialIndicesBase, (indices->Length / 3) * sizeof(int));


	UnmanagedPointer = new btTriangleIndexVertexMaterialArray(
		indices->Length / 3, indicesArray, 3 * sizeof(int),
		vertices->Length, verticesArray[0], sizeof(btVector3),
		materials->Length, materialsArray, materials[0].SizeInBytes,
		materialIndicesArray, sizeof(int)
	);

	// Don't delete[] the arrays here, the object will use them.
}
