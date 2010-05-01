#include "StdAfx.h"

#include "StaticPlaneShape.h"

StaticPlaneShape::StaticPlaneShape(btStaticPlaneShape* shape)
: BulletSharp::ConcaveShape(shape)
{
}

StaticPlaneShape::StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant)
: BulletSharp::ConcaveShape(0)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	UnmanagedPointer = new btStaticPlaneShape(*planeNormalTemp, planeConstant);
	delete planeNormalTemp;
}

btScalar StaticPlaneShape::PlaneConstant::get()
{
	return UnmanagedPointer->getPlaneConstant();
}

Vector3 StaticPlaneShape::PlaneNormal::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getPlaneNormal());
}

btStaticPlaneShape* StaticPlaneShape::UnmanagedPointer::get()
{
	return (btStaticPlaneShape*)ConcaveShape::UnmanagedPointer;
}
