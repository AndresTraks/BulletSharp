#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "DataStream.h"
#include "TriangleIndexVertexMaterialArray.h"

MaterialProperties::~MaterialProperties()
{
	this->!MaterialProperties();
}

MaterialProperties::!MaterialProperties()
{
	if (_native)
	{
		Free();
		delete _native;
		_native = NULL;
	}
}

MaterialProperties::MaterialProperties()
{
	_native = new btMaterialProperties();
}

void MaterialProperties::Allocate(int numMaterials, int numTriangles, int materialStride, int materialIndexStride,
	PhyScalarType materialType, PhyScalarType triangleType)
{
	if (_ownsData)
	{
		Free();
	}
	else
	{
		_ownsData = true;
	}

	_native->m_numMaterials = numMaterials;
	_native->m_materialBase = new unsigned char[numMaterials * materialStride];
	_native->m_materialStride = materialStride;
	_native->m_materialType = (PHY_ScalarType)materialType;

	_native->m_numTriangles = numTriangles;
	_native->m_triangleMaterialsBase = new unsigned char[numTriangles * materialIndexStride];
	_native->m_triangleMaterialStride = materialIndexStride;
	_native->m_triangleType = (PHY_ScalarType)triangleType;
}

void MaterialProperties::Free()
{
	if (_ownsData)
	{
		delete[] _native->m_materialBase;
		delete[] _native->m_triangleMaterialsBase;
		_native->m_materialBase = 0;
		_native->m_triangleMaterialsBase = 0;
		_ownsData = false;
	}
}

IntPtr MaterialProperties::MaterialBase::get()
{
	return IntPtr((void*)_native->m_materialBase);
}
void MaterialProperties::MaterialBase::set(IntPtr value)
{
	_native->m_materialBase = (const unsigned char *)value.ToPointer();
}

int MaterialProperties::MaterialStride::get()
{
	return _native->m_materialStride;
}
void MaterialProperties::MaterialStride::set(int value)
{
	_native->m_materialStride = value;
}

PhyScalarType MaterialProperties::MaterialType::get()
{
	return (PhyScalarType)_native->m_materialType;
}
void MaterialProperties::MaterialType::set(PhyScalarType value)
{
	_native->m_materialType = (PHY_ScalarType)value;
}

int MaterialProperties::NumMaterials::get()
{
	return _native->m_numMaterials;
}
void MaterialProperties::NumMaterials::set(int value)
{
	_native->m_numMaterials = value;
}

int MaterialProperties::NumTriangles::get()
{
	return _native->m_numTriangles;
}
void MaterialProperties::NumTriangles::set(int value)
{
	_native->m_numTriangles = value;
}

IntPtr MaterialProperties::TriangleMaterialsBase::get()
{
	return IntPtr((void*)_native->m_triangleMaterialsBase);
}
void MaterialProperties::TriangleMaterialsBase::set(IntPtr value)
{
	_native->m_triangleMaterialsBase = (const unsigned char *)value.ToPointer();
}

int MaterialProperties::TriangleMaterialStride::get()
{
	return _native->m_triangleMaterialStride;
}
void MaterialProperties::TriangleMaterialStride::set(int value)
{
	_native->m_triangleMaterialStride = value;
}

PhyScalarType MaterialProperties::TriangleType::get()
{
	return (PhyScalarType)_native->m_triangleType;
}
void MaterialProperties::TriangleType::set(PhyScalarType value)
{
	_native->m_triangleType = (PHY_ScalarType)value;
}


#define Native static_cast<btTriangleIndexVertexMaterialArray*>(_native)

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(btTriangleIndexVertexMaterialArray* native)
	: TriangleIndexVertexArray(native)
{
	_materialProperties = gcnew List<MaterialProperties^>();
}

TriangleIndexVertexMaterialArray::~TriangleIndexVertexMaterialArray()
{
	this->!TriangleIndexVertexMaterialArray();
}

TriangleIndexVertexMaterialArray::!TriangleIndexVertexMaterialArray()
{
	if (_initialMesh)
	{
		delete _initialMesh;
		_initialMesh = nullptr;
	}

	if (_initialMaterialProperties)
	{
		delete _initialMaterialProperties;
		_initialMaterialProperties = nullptr;
	}
}

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray()
	: TriangleIndexVertexArray(new btTriangleIndexVertexMaterialArray())
{
	_materialProperties = gcnew List<MaterialProperties^>();
}

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(int numTriangles, IntPtr triangleIndexBase,
	int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride, int numMaterials,
	IntPtr materialBase, int materialStride, IntPtr triangleMaterialsBase, int materialIndexStride)
: TriangleIndexVertexArray(new btTriangleIndexVertexMaterialArray(numTriangles, (int*)triangleIndexBase.ToPointer(),
	triangleIndexStride, numVertices, (btScalar*)vertexBase.ToPointer(), vertexStride, numMaterials,
	(unsigned char*)materialBase.ToPointer(), materialStride, (int*)triangleMaterialsBase.ToPointer(), materialIndexStride))
{
	_materialProperties = gcnew List<MaterialProperties^>();
}

TriangleIndexVertexMaterialArray::TriangleIndexVertexMaterialArray(ICollection<int>^ indices, ICollection<Vector3>^ vertices,
	ICollection<BulletMaterial>^ materials, ICollection<int>^ materialIndices)
: TriangleIndexVertexArray(new btTriangleIndexVertexMaterialArray())
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
	Marshal::Copy(indexArray, 0, _initialMesh->TriangleIndexBase, indexArray->Length);

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

	AddIndexedMesh(_initialMesh);


	_initialMaterialProperties = gcnew MaterialProperties();
	_initialMaterialProperties->Allocate(materials->Count, materialIndices->Count, sizeof(btMaterial), sizeof(int),
		PhyScalarType::Single, PhyScalarType::Int32);

	array<BulletMaterial>^ materialArray = dynamic_cast<array<BulletMaterial>^>(materials);
	if (!materialArray)
	{
		materialArray = gcnew array<BulletMaterial>(materials->Count);
		materials->CopyTo(materialArray, 0);
	}
	pin_ptr<BulletMaterial> materialsBase = &materialArray[0];
	memcpy(_initialMaterialProperties->MaterialBase.ToPointer(), (unsigned char*)materialsBase, materialArray->Length * sizeof(btMaterial));

	array<int>^ materialIndexArray = dynamic_cast<array<int>^>(materialIndices);
	if (!materialIndexArray)
	{
		materialIndexArray = gcnew array<int>(materialIndices->Count);
		materialIndices->CopyTo(materialIndexArray, 0);
	}
	Marshal::Copy(materialIndexArray, 0, _initialMaterialProperties->TriangleMaterialsBase, materialIndexArray->Length);

	_materialProperties = gcnew List<MaterialProperties^>();
	AddMaterialProperties(_initialMaterialProperties);
}

void TriangleIndexVertexMaterialArray::AddMaterialProperties(MaterialProperties^ mat, PhyScalarType triangleType)
{
	_materialProperties->Add(mat);
	Native->addMaterialProperties(*mat->_native, (PHY_ScalarType)triangleType);
}

void TriangleIndexVertexMaterialArray::AddMaterialProperties(MaterialProperties^ mat)
{
	_materialProperties->Add(mat);
	Native->addMaterialProperties(*mat->_native);
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

	Native->getLockedMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
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

	Native->getLockedMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
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

	Native->getLockedReadOnlyMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
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

	Native->getLockedReadOnlyMaterialBase(&materialDataTemp, numMaterialsTemp, materialTypeTemp,
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

#endif
