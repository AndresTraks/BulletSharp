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
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_stridingMesh->calculateAabbBruteForce(*tmpAabbMin, *tmpAabbMax);
	
	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);

	delete tmpAabbMin;
	delete tmpAabbMax;
}

btStridingMeshInterface* StridingMeshInterface::UnmanagedPointer::get()
{
	return _stridingMesh;
}
