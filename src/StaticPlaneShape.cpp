#include "StdAfx.h"

#include "StaticPlaneShape.h"

StaticPlaneShape::StaticPlaneShape(btStaticPlaneShape* shape)
: BulletSharp::ConcaveShape(shape)
{
}

StaticPlaneShape::StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant)
: BulletSharp::ConcaveShape(0)
{
	VECTOR3_DEF(planeNormal);
	UnmanagedPointer = new btStaticPlaneShape(VECTOR3_USE(planeNormal), planeConstant);
	VECTOR3_DEL(planeNormal);
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
