#include "StdAfx.h"

#include "MultiSphereShape.h"

#define Unmanaged static_cast<btMultiSphereShape*>(_unmanaged)

MultiSphereShape::MultiSphereShape(btMultiSphereShape* shape)
: ConvexInternalAabbCachingShape(shape)
{
}

MultiSphereShape::MultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
: ConvexInternalAabbCachingShape(0)
{
	int numSpheres = (positions->Length < radi->Length) ? positions->Length : radi->Length;

	btVector3* positionsTemp = Math::Vector3ArrayToUnmanaged(positions);
	btScalar* radiTemp = Math::BtScalarArrayToUnmanaged(radi, numSpheres);

	UnmanagedPointer = new btMultiSphereShape(positionsTemp, radiTemp, numSpheres);

	delete[] positionsTemp;
	delete[] radiTemp;
}

Vector3 MultiSphereShape::GetSpherePosition(int index)
{
	return Math::BtVector3ToVector3(&Unmanaged->getSpherePosition(index));
}

btScalar MultiSphereShape::GetSphereRadius(int index)
{
	return Unmanaged->getSphereRadius(index);
}

int MultiSphereShape::SphereCount::get()
{
	return Unmanaged->getSphereCount();
}
