#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "DataStream.h"
#include "TriangleIndexVertexMaterialArray.h"

MaterialProperties::MaterialProperties()
{
	_properties = new btMaterialProperties();
}

IntPtr MaterialProperties::MaterialBase::get()
{
	return IntPtr((void*)_properties->m_materialBase);
}
void MaterialProperties::MaterialBase::set(IntPtr value)
{
	_properties->m_materialBase = (const unsigned char *)value.ToPointer();
}

int MaterialProperties::MaterialStride::get()
{
	return _properties->m_materialStride;
}
void MaterialProperties::MaterialStride::set(int value)
{
	_properties->m_materialStride = value;
}

PhyScalarType MaterialProperties::MaterialType::get()
{
	return (PhyScalarType)_properties->m_materialType;
}
void MaterialProperties::MaterialType::set(PhyScalarType value)
{
	_properties->m_materialType = (PHY_ScalarType)value;
}

int MaterialProperties::NumMaterials::get()
{
	return _properties->m_numMaterials;
}
void MaterialProperties::NumMaterials::set(int value)
{
	_properties->m_numMaterials = value;
}

int MaterialProperties::NumTriangles::get()
{
	return _properties->m_numTriangles;
}
void MaterialProperties::NumTriangles::set(int value)
{
	_properties->m_numTriangles = value;
}

IntPtr MaterialProperties::TriangleMaterialsBase::get()
{
	return IntPtr((void*)_properties->m_triangleMaterialsBase);
}
void MaterialProperties::TriangleMaterialsBase::set(IntPtr value)
{
	_properties->m_triangleMaterialsBase = (const unsigned char *)value.ToPointer();
}

int MaterialProperties::TriangleMaterialStride::get()
{
	return _properties->m_triangleMaterialStride;
}
void MaterialProperties::TriangleMaterialStride::set(int value)
{
	_properties->m_triangleMaterialStride = value;
}

PhyScalarType MaterialProperties::TriangleType::get()
{
	return (PhyScalarType)_properties->m_triangleType;
}
void MaterialProperties::TriangleType::set(PhyScalarType value)
{
	_properties->m_triangleType = (PHY_ScalarType)value;
}

btMaterialProperties* MaterialProperties::UnmanagedPointer::get()
{
	return _properties;
}


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
	int* indicesArray = Math::IntArrayToUnmanaged(indices);
	btVector3* verticesArray = Math::Vector3ArrayToUnmanaged(vertices);

	// Materials
	pin_ptr<BulletMaterial> materialsBase = &materials[0];
	unsigned char* materialsArray = new unsigned char[materials->Length * BulletMaterial::SizeInBytes];
	memcpy(materialsArray, (unsigned char*)materialsBase, materials->Length * BulletMaterial::SizeInBytes);
	int* materialIndicesArray = Math::IntArrayToUnmanaged(indices, indices->Length / 3);

	UnmanagedPointer = new btTriangleIndexVertexMaterialArray(
		indices->Length / 3, indicesArray, 3 * sizeof(int),
		vertices->Length, verticesArray[0], sizeof(btVector3),
		materials->Length, materialsArray, materials[0].SizeInBytes,
		materialIndicesArray, sizeof(int)
	);

	// Don't delete[] the arrays here, the object will use them.
}

void TriangleIndexVertexMaterialArray::AddMaterialProperties(MaterialProperties^ mat, PhyScalarType triangleType)
{
	UnmanagedPointer->addMaterialProperties(*mat->UnmanagedPointer, (PHY_ScalarType)triangleType);
}

void TriangleIndexVertexMaterialArray::GetLockedMaterialData([Out] BulletSharp::DataStream^% materialData,
	[Out] int% numMaterials, [Out] PhyScalarType% materialType, [Out] int% materialStride,
	[Out] BulletSharp::DataStream^% triangleMaterialData, [Out] int% numTriangles,
	[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType, int subpart)
{
	unsigned char* materialDataTemp;
	int numMaterialsTemp;
	PHY_ScalarType materialTypeTemp;
	int materialStrideTemp;
	unsigned char* triangleMaterialDataTemp;
	int numTrianglesTemp;
	int triangleMaterialStrideTemp;
	PHY_ScalarType triangleTypeTemp;

	UnmanagedPointer->getLockedMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
		materialStrideTemp, &triangleMaterialDataTemp, numTrianglesTemp, triangleMaterialStrideTemp, triangleTypeTemp, subpart);

	numMaterials = numMaterialsTemp;
	materialType = (PhyScalarType)materialTypeTemp;
	materialStride = materialStrideTemp;
	numTriangles = numTrianglesTemp;
	triangleMaterialStride = triangleMaterialStrideTemp;
	triangleType = (PhyScalarType)triangleTypeTemp;

	materialData = gcnew BulletSharp::DataStream((void*)materialDataTemp, numMaterials * materialStride, true, true, false);
	triangleMaterialData = gcnew BulletSharp::DataStream((void*)triangleMaterialDataTemp, numTrianglesTemp * triangleMaterialStrideTemp, true, true, false);
}

void TriangleIndexVertexMaterialArray::GetLockedMaterialData([Out] BulletSharp::DataStream^% materialData,
	[Out] int% numMaterials, [Out] PhyScalarType% materialType, [Out] int% materialStride,
	[Out] BulletSharp::DataStream^% triangleMaterialData, [Out] int% numTriangles,
	[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType)
{
	unsigned char* materialDataTemp;
	int numMaterialsTemp;
	PHY_ScalarType materialTypeTemp;
	int materialStrideTemp;
	unsigned char* triangleMaterialDataTemp;
	int numTrianglesTemp;
	int triangleMaterialStrideTemp;
	PHY_ScalarType triangleTypeTemp;

	UnmanagedPointer->getLockedMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
		materialStrideTemp, &triangleMaterialDataTemp, numTrianglesTemp, triangleMaterialStrideTemp, triangleTypeTemp);

	numMaterials = numMaterialsTemp;
	materialType = (PhyScalarType)materialTypeTemp;
	materialStride = materialStrideTemp;
	numTriangles = numTrianglesTemp;
	triangleMaterialStride = triangleMaterialStrideTemp;
	triangleType = (PhyScalarType)triangleTypeTemp;

	materialData = gcnew BulletSharp::DataStream((void*)materialDataTemp, numMaterials * materialStride, true, true, false);
	triangleMaterialData = gcnew BulletSharp::DataStream((void*)triangleMaterialDataTemp, numTrianglesTemp * triangleMaterialStrideTemp, true, true, false);
}

void TriangleIndexVertexMaterialArray::GetLockedReadOnlyMaterialData([Out] BulletSharp::DataStream^% materialData,
	[Out] int% numMaterials, [Out] PhyScalarType% materialType, [Out] int% materialStride,
	[Out] BulletSharp::DataStream^% triangleMaterialData, [Out] int% numTriangles,
	[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType, int subpart)
{
	const unsigned char* materialDataTemp;
	int numMaterialsTemp;
	PHY_ScalarType materialTypeTemp;
	int materialStrideTemp;
	const unsigned char* triangleMaterialDataTemp;
	int numTrianglesTemp;
	int triangleMaterialStrideTemp;
	PHY_ScalarType triangleTypeTemp;

	UnmanagedPointer->getLockedReadOnlyMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
		materialStrideTemp, &triangleMaterialDataTemp, numTrianglesTemp, triangleMaterialStrideTemp, triangleTypeTemp, subpart);

	numMaterials = numMaterialsTemp;
	materialType = (PhyScalarType)materialTypeTemp;
	materialStride = materialStrideTemp;
	numTriangles = numTrianglesTemp;
	triangleMaterialStride = triangleMaterialStrideTemp;
	triangleType = (PhyScalarType)triangleTypeTemp;

	materialData = gcnew BulletSharp::DataStream((void*)materialDataTemp, numMaterials * materialStride, true, false, false);
	triangleMaterialData = gcnew BulletSharp::DataStream((void*)triangleMaterialDataTemp, numTrianglesTemp * triangleMaterialStrideTemp, true, false, false);
}

void TriangleIndexVertexMaterialArray::GetLockedReadOnlyMaterialData([Out] BulletSharp::DataStream^% materialData,
	[Out] int% numMaterials, [Out] PhyScalarType% materialType, [Out] int% materialStride,
	[Out] BulletSharp::DataStream^% triangleMaterialData, [Out] int% numTriangles,
	[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType)
{
	const unsigned char* materialDataTemp;
	int numMaterialsTemp;
	PHY_ScalarType materialTypeTemp;
	int materialStrideTemp;
	const unsigned char* triangleMaterialDataTemp;
	int numTrianglesTemp;
	int triangleMaterialStrideTemp;
	PHY_ScalarType triangleTypeTemp;

	UnmanagedPointer->getLockedReadOnlyMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
		materialStrideTemp, &triangleMaterialDataTemp, numTrianglesTemp, triangleMaterialStrideTemp, triangleTypeTemp);

	numMaterials = numMaterialsTemp;
	materialType = (PhyScalarType)materialTypeTemp;
	materialStride = materialStrideTemp;
	numTriangles = numTrianglesTemp;
	triangleMaterialStride = triangleMaterialStrideTemp;
	triangleType = (PhyScalarType)triangleTypeTemp;

	materialData = gcnew BulletSharp::DataStream((void*)materialDataTemp, numMaterials * materialStride, true, false, false);
	triangleMaterialData = gcnew BulletSharp::DataStream((void*)triangleMaterialDataTemp, numTrianglesTemp * triangleMaterialStrideTemp, true, false, false);
}

btTriangleIndexVertexMaterialArray* TriangleIndexVertexMaterialArray::UnmanagedPointer::get()
{
	return (btTriangleIndexVertexMaterialArray*)TriangleIndexVertexArray::UnmanagedPointer;
}

#endif
