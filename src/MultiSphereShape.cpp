#include "StdAfx.h"

#include "MultiSphereShape.h"

MultiSphereShape::MultiSphereShape(btMultiSphereShape* shape)
: ConvexInternalAabbCachingShape(shape)
{
}

MultiSphereShape::MultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
: ConvexInternalAabbCachingShape(0)
{
	int numSpheres = (positions->Length < radi->Length) ? positions->Length : radi->Length;

	btVector3* positionsTemp = new btVector3[numSpheres];
	btScalar* radiTemp = new btScalar[numSpheres];
	int i;

	for(i=0; i<numSpheres; i++)
		Math::Vector3ToBtVector3(positions[i], &positionsTemp[i]);

	for(i=0; i<numSpheres; i++)
		radiTemp[i] = radi[i];

	UnmanagedPointer = new btMultiSphereShape(positionsTemp, radiTemp, numSpheres);

	delete positionsTemp;
	delete radiTemp;
}

Vector3 MultiSphereShape::GetSpherePosition(int index)
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getSpherePosition(index));
}

btScalar MultiSphereShape::GetSphereRadius(int index)
{
	return UnmanagedPointer->getSphereRadius(index);
}

int MultiSphereShape::SphereCount::get()
{
	return UnmanagedPointer->getSphereCount();
}

btMultiSphereShape* MultiSphereShape::UnmanagedPointer::get()
{
	return (btMultiSphereShape*)ConvexInternalAabbCachingShape::UnmanagedPointer;
}
