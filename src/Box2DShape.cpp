#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Box2DShape.h"
#include "Collections.h"

#define Native static_cast<btBox2dShape*>(_native)

Box2DShape::Box2DShape(btBox2dShape* native)
	: PolyhedralConvexShape(native)
{
}

Box2DShape::Box2DShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(0)
{
	VECTOR3_DEF(boxHalfExtents);
	UnmanagedPointer = new btBox2dShape(VECTOR3_USE(boxHalfExtents));
	VECTOR3_DEL(boxHalfExtents);
}

Box2DShape::Box2DShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = ALIGNED_NEW(btVector3) (boxHalfExtentsX, boxHalfExtentsY, boxHalfExtentsZ);
	UnmanagedPointer = new btBox2dShape(*boxHalfExtentsTemp);
	ALIGNED_FREE(boxHalfExtentsTemp);
}

Box2DShape::Box2DShape(btScalar boxHalfExtents)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = ALIGNED_NEW(btVector3) (boxHalfExtents, boxHalfExtents, boxHalfExtents);
	UnmanagedPointer = new btBox2dShape(*boxHalfExtentsTemp);
	ALIGNED_FREE(boxHalfExtentsTemp);
}

Vector3 Box2DShape::GetVertex(int i)
{
	btVector3* vertexTemp = ALIGNED_NEW(btVector3);
	Native->getVertex(i, *vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	ALIGNED_FREE(vertexTemp);
	return vertex;
}

Vector4 Box2DShape::GetPlaneEquation(int i)
{
	btVector4* equationTemp = new btVector4;
	Native->getPlaneEquation(*equationTemp, i);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 Box2DShape::Centroid::get()
{
	return Math::BtVector3ToVector3(&Native->getCentroid());
}

Vector3 Box2DShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = ALIGNED_NEW(btVector3) (Native->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	ALIGNED_FREE(extentsTemp);
	return extents;
}

Vector3 Box2DShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&Native->getHalfExtentsWithoutMargin());
}

Vector3Array^ Box2DShape::Normals::get()
{
	const btVector3* normals = Native->getNormals();
	ReturnCachedObjectStaticParam(Vector3Array, _normals, normals, 4);
}

Vector3Array^ Box2DShape::Vertices::get()
{
	const btVector3* vertices = Native->getVertices();
	ReturnCachedObjectStaticParam(Vector3Array, _vertices, vertices, 4);
}

#endif
