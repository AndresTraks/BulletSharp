#include "StdAfx.h"

#include "DataStream.h"
#include "StridingMeshInterface.h"
#include "TriangleCallback.h"
#include "TriangleIndexVertexArray.h"
#include "TriangleMesh.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "TriangleIndexVertexMaterialArray.h"
#endif

StridingMeshInterface::StridingMeshInterface(btStridingMeshInterface* native)
{
	_native = native;
}

StridingMeshInterface^ StridingMeshInterface::GetManaged(btStridingMeshInterface* stridingMesh)
{
	if (stridingMesh == nullptr)
		return nullptr;

	btTriangleMesh* triangleMesh = static_cast<btTriangleMesh*>(stridingMesh);
	if (triangleMesh != 0)
		return gcnew TriangleMesh(triangleMesh);

#ifndef DISABLE_UNCOMMON
	btTriangleIndexVertexMaterialArray* triangleIndexVertexMaterialArray = static_cast<btTriangleIndexVertexMaterialArray*>(stridingMesh);
	if (triangleIndexVertexMaterialArray != 0)
		return gcnew TriangleIndexVertexMaterialArray(triangleIndexVertexMaterialArray);
#endif

	btTriangleIndexVertexArray* triangleIndexVertexArray = static_cast<btTriangleIndexVertexArray*>(stridingMesh);
	if (triangleIndexVertexArray != 0)
		return gcnew TriangleIndexVertexArray(triangleIndexVertexArray);

	throw gcnew NotImplementedException();
}

StridingMeshInterface::~StridingMeshInterface()
{
	this->!StridingMeshInterface();
}

StridingMeshInterface::!StridingMeshInterface()
{
	if (this->IsDisposed)
		return;
	
	delete _native;
	_native = NULL;
}

void StridingMeshInterface::CalculateAabbBruteForce(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->calculateAabbBruteForce(*aabbMinTemp, *aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

#ifndef DISABLE_SERIALIZE
int StridingMeshInterface::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}
#endif

void StridingMeshInterface::GetLockedReadOnlyVertexIndexData([Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts,
	[Out] PhyScalarType% type, [Out] int% vertexStride, [Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces,
	[Out] PhyScalarType% indicesType, int subpart)
{
	const unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	const unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;
	_native->getLockedReadOnlyVertexIndexBase(&vertexBaseTemp, numVertsTemp,
		typeTemp, vertexStrideTemp, &indexBaseTemp, indexStrideTemp,
		numFacesTemp, indicestypeTemp, subpart);
	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;
	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, false, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, false, false);
}

void StridingMeshInterface::GetLockedReadOnlyVertexIndexData([Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts,
	[Out] PhyScalarType% type, [Out] int% vertexStride, [Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces,
	[Out] PhyScalarType% indicesType)
{
	const unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	const unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;
	_native->getLockedReadOnlyVertexIndexBase(&vertexBaseTemp, numVertsTemp,
		typeTemp, vertexStrideTemp, &indexBaseTemp, indexStrideTemp,
		numFacesTemp, indicestypeTemp);
	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;
	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, false, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, false, false);
}

void StridingMeshInterface::GetLockedVertexIndexData([Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts,
	[Out] PhyScalarType% type, [Out] int% vertexStride, [Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces,
	[Out] PhyScalarType% indicesType, int subpart)
{
	unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;
	_native->getLockedVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp,
		indicestypeTemp, subpart);
	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;

	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, true, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, true, false);
}

void StridingMeshInterface::GetLockedVertexIndexData([Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts,
	[Out] PhyScalarType% type, [Out] int% vertexStride, [Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces,
	[Out] PhyScalarType% indicesType)
{
	unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;
	_native->getLockedVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp,
		indicestypeTemp);
	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;

	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, true, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, true, false);
}

void StridingMeshInterface::GetPremadeAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->getPremadeAabb(aabbMinTemp, aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

#ifndef DISABLE_INTERNAL
void StridingMeshInterface::InternalProcessAllTriangles(InternalTriangleIndexCallback^ callback,
	Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->InternalProcessAllTriangles(callback->_native, VECTOR3_USE(aabbMin),
		VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}
#endif

void StridingMeshInterface::PreallocateIndices(int numIndices)
{
	_native->preallocateIndices(numIndices);
}

void StridingMeshInterface::PreallocateVertices(int numVerts)
{
	_native->preallocateVertices(numVerts);
}

#ifndef DISABLE_SERIALIZE
String^ StridingMeshInterface::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}
#endif

void StridingMeshInterface::SetPremadeAabb(Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	_native->setPremadeAabb(VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void StridingMeshInterface::UnlockReadOnlyVertexData(int subpart)
{
	_native->unLockReadOnlyVertexBase(subpart);
}

void StridingMeshInterface::UnlockVertexData(int subpart)
{
	_native->unLockVertexBase(subpart);
}

bool StridingMeshInterface::HasPremadeAabb::get()
{
	return _native->hasPremadeAabb();
}

bool StridingMeshInterface::IsDisposed::get()
{
	return ( _native == NULL );
}

int StridingMeshInterface::NumSubParts::get()
{
	return _native->getNumSubParts();
}

Vector3 StridingMeshInterface::Scaling::get()
{
	return Math::BtVector3ToVector3(&_native->getScaling());
}
void StridingMeshInterface::Scaling::set(Vector3 scaling)
{
	VECTOR3_CONV(scaling);
	_native->setScaling(VECTOR3_USE(scaling));
	VECTOR3_DEL(scaling);
}
