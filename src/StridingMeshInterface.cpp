#include "StdAfx.h"

#include "DataStream.h"
#include "StridingMeshInterface.h"
#include "TriangleCallback.h"
#include "TriangleIndexVertexArray.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

StridingMeshInterface::StridingMeshInterface(btStridingMeshInterface* stridingMesh)
{
	_stridingMesh = stridingMesh;
}

StridingMeshInterface^ StridingMeshInterface::UpcastDetect()
{
	if (_stridingMesh == nullptr)
		return nullptr;

	void* ptr;

	ptr = static_cast<btTriangleIndexVertexArray*>(_stridingMesh);
	if (ptr != 0)
		return gcnew TriangleIndexVertexArray((btTriangleIndexVertexArray*)ptr);

	return this;
}

StridingMeshInterface::~StridingMeshInterface()
{
	this->!StridingMeshInterface();
}

StridingMeshInterface::!StridingMeshInterface()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );

	_stridingMesh = NULL;

	OnDisposed( this, nullptr );
}

bool StridingMeshInterface::IsDisposed::get()
{
	return ( _stridingMesh == NULL );
}

void StridingMeshInterface::CalculateAabbBruteForce(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	_stridingMesh->calculateAabbBruteForce(*aabbMinTemp, *aabbMaxTemp);
	
	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

#ifndef DISABLE_SERIALIZE
int StridingMeshInterface::CalculateSerializeBufferSize()
{
	return _stridingMesh->calculateSerializeBufferSize();
}

String^ StridingMeshInterface::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = _stridingMesh->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	if (name == 0)
		return nullptr;

	return gcnew String(name);
}
#endif

void StridingMeshInterface::GetLockedReadOnlyVertexIndexData(
	[Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type, [Out] int% vertexStride,
	[Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType,
	int subpart)
{
	const unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	const unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;

	UnmanagedPointer->getLockedReadOnlyVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp, indicestypeTemp, subpart);

	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;

	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, false, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, false, false);
}

void StridingMeshInterface::GetLockedReadOnlyVertexIndexData(
	[Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type, [Out] int% vertexStride,
	[Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType)
{
	const unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	const unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;

	UnmanagedPointer->getLockedReadOnlyVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp, indicestypeTemp);

	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;

	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, false, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, false, false);
}

void StridingMeshInterface::GetLockedVertexIndexData(
	[Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type, [Out] int% vertexStride,
	[Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType,
	int subpart)
{
	unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;

	UnmanagedPointer->getLockedVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp, indicestypeTemp, subpart);

	numVerts = numVertsTemp;
	type = (PhyScalarType)typeTemp;
	vertexStride = vertexStrideTemp;
	indexStride = indexStrideTemp;
	numFaces = numFacesTemp;
	indicesType = (PhyScalarType)indicestypeTemp;

	vertexData = gcnew BulletSharp::DataStream((void*)vertexBaseTemp, numVerts * vertexStride, true, true, false);
	indexData = gcnew BulletSharp::DataStream((void*)indexBaseTemp, numFaces * indexStride, true, true, false);
}

void StridingMeshInterface::GetLockedVertexIndexData(
	[Out] BulletSharp::DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type, [Out] int% vertexStride,
	[Out] BulletSharp::DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType)
{
	unsigned char* vertexBaseTemp;
	int numVertsTemp;
	PHY_ScalarType typeTemp;
	int vertexStrideTemp;
	unsigned char* indexBaseTemp;
	int indexStrideTemp;
	int numFacesTemp;
	PHY_ScalarType indicestypeTemp;

	UnmanagedPointer->getLockedVertexIndexBase(&vertexBaseTemp, numVertsTemp, typeTemp,
		vertexStrideTemp, &indexBaseTemp, indexStrideTemp, numFacesTemp, indicestypeTemp);

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
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	_stridingMesh->getPremadeAabb(aabbMinTemp, aabbMaxTemp);
	
	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

#ifndef DISABLE_INTERNAL
void StridingMeshInterface::InternalProcessAllTriangles(InternalTriangleIndexCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);
	
	_stridingMesh->InternalProcessAllTriangles(callback->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}
#endif

void StridingMeshInterface::PreallocateIndices(int numIndices)
{
	_stridingMesh->preallocateIndices(numIndices);
}

void StridingMeshInterface::PreallocateVertices(int numVerts)
{
	_stridingMesh->preallocateIndices(numVerts);
}

void StridingMeshInterface::SetPremadeAabb(Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	_stridingMesh->setPremadeAabb(*aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void StridingMeshInterface::UnlockReadOnlyVertexData(int subpart)
{
	_stridingMesh->unLockReadOnlyVertexBase(subpart);
}

void StridingMeshInterface::UnlockVertexData(int subpart)
{
	_stridingMesh->unLockVertexBase(subpart);
}

bool StridingMeshInterface::HasPremadeAabb::get()
{
	return _stridingMesh->hasPremadeAabb();
}

int StridingMeshInterface::NumSubParts::get()
{
	return _stridingMesh->getNumSubParts();
}

Vector3 StridingMeshInterface::Scaling::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getScaling());
}
void StridingMeshInterface::Scaling::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setScaling(*valueTemp);
	delete valueTemp;
}

btStridingMeshInterface* StridingMeshInterface::UnmanagedPointer::get()
{
	return _stridingMesh;
}
void StridingMeshInterface::UnmanagedPointer::set(btStridingMeshInterface* value)
{
	_stridingMesh = value;
}
