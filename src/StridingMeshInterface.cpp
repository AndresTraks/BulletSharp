#include "StdAfx.h"

#include "StridingMeshInterface.h"

StridingMeshInterface::StridingMeshInterface(btStridingMeshInterface* stridingMesh)
{
	_stridingMesh = stridingMesh;
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
