#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Box2dShape.h"
#include "Collections.h"

#define Native static_cast<btBox2dShape*>(_native)

Box2dShape::Box2dShape(btBox2dShape* shape)
: PolyhedralConvexShape(shape)
{
}

Box2dShape::Box2dShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(0)
{
	VECTOR3_DEF(boxHalfExtents);
	UnmanagedPointer = new btBox2dShape(VECTOR3_USE(boxHalfExtents));
	VECTOR3_DEL(boxHalfExtents);
}

Box2dShape::Box2dShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = new btVector3(boxHalfExtentsX, boxHalfExtentsY, boxHalfExtentsZ);
	UnmanagedPointer = new btBox2dShape(*boxHalfExtentsTemp);
	delete boxHalfExtentsTemp;
}

Box2dShape::Box2dShape(btScalar boxHalfExtents)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = new btVector3(boxHalfExtents, boxHalfExtents, boxHalfExtents);
	UnmanagedPointer = new btBox2dShape(*boxHalfExtentsTemp);
	delete boxHalfExtentsTemp;
}

Vector3 Box2dShape::GetVertex(int i)
{
	btVector3* vertexTemp = new btVector3;
	Native->getVertex(i, *vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	delete vertexTemp;
	return vertex;
}

Vector4 Box2dShape::GetPlaneEquation(int i)
{
	btVector4* equationTemp = new btVector4;
	Native->getPlaneEquation(*equationTemp, i);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 Box2dShape::Centroid::get()
{
	return Math::BtVector3ToVector3(&Native->getCentroid());
}

Vector3 Box2dShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = new btVector3(Native->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	delete extentsTemp;
	return extents;
}

Vector3 Box2dShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&Native->getHalfExtentsWithoutMargin());
}

Vector3Array^ Box2dShape::Normals::get()
{
	const btVector3* normals = Native->getNormals();
	ReturnCachedObjectStaticParam(Vector3Array, _normals, normals, 4);
}

int Box2dShape::VertexCount::get()
{
	return Native->getVertexCount();
}

Vector3Array^ Box2dShape::Vertices::get()
{
	const btVector3* vertices = Native->getVertices();
	ReturnCachedObjectStaticParam(Vector3Array, _vertices, vertices, 4);
}

#endif
