#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Box2dShape.h"
#include "Collections.h"

#define Unmanaged static_cast<btBox2dShape*>(_unmanaged)

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
	Unmanaged->getVertex(i, *vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	delete vertexTemp;
	return vertex;
}

Vector4 Box2dShape::GetPlaneEquation(int i)
{
	btVector4* equationTemp = new btVector4;
	Unmanaged->getPlaneEquation(*equationTemp, i);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 Box2dShape::Centroid::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getCentroid());
}

Vector3 Box2dShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = new btVector3(Unmanaged->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	delete extentsTemp;
	return extents;
}

Vector3 Box2dShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getHalfExtentsWithoutMargin());
}

Vector3Array^ Box2dShape::Normals::get()
{
	const btVector3* normals = Unmanaged->getNormals();
	ReturnCachedObjectStatic(Vector3Array, _normals, normals, 4);
}

int Box2dShape::VertexCount::get()
{
	return Unmanaged->getVertexCount();
}

Vector3Array^ Box2dShape::Vertices::get()
{
	const btVector3* vertices = Unmanaged->getVertices();
	ReturnCachedObjectStatic(Vector3Array, _vertices, vertices, 4);
}

#endif
