#include "StdAfx.h"

#include "StaticPlaneShape.h"

StaticPlaneShape::StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant)
: BulletSharp::ConcaveShape(new btStaticPlaneShape(*Math::Vector3ToBtVector3(planeNormal), planeConstant))
{
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
