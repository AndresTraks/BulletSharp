#include "StdAfx.h"

#include "StridingMeshInterface.h"
#include "TriangleIndexVertexArray.h"

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

btStridingMeshInterface* StridingMeshInterface::UnmanagedPointer::get()
{
	return _stridingMesh;
}
