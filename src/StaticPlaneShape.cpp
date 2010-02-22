#include "StdAfx.h"

#include "StaticPlaneShape.h"

StaticPlaneShape::StaticPlaneShape(Vector3 planeNormal, btScalar planeConstant)
: BulletSharp::ConcaveShape(new btStaticPlaneShape(*Math::Vector3ToBtVec3(planeNormal), planeConstant))
{
}

btStaticPlaneShape* StaticPlaneShape::UnmanagedPointer::get()
{
	return (btStaticPlaneShape*)ConcaveShape::UnmanagedPointer;
}
