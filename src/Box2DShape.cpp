#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Box2DShape.h"
#include "Collections.h"

#define Native static_cast<btBox2dShape*>(_native)

Box2DShape::Box2DShape(Vector3 boxHalfExtents)
	: PolyhedralConvexShape(0)
{
	VECTOR3_CONV(boxHalfExtents);
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

Vector4 Box2DShape::GetPlaneEquation(int i)
{
	btVector4* equationTemp = ALIGNED_NEW(btVector4);
	Native->getPlaneEquation(*equationTemp, i);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	ALIGNED_FREE(equationTemp);
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
	if (_normals == nullptr)
	{
		_normals = gcnew Vector3Array(Native->getNormals(), 4);
	}
	return _normals;
}

Vector3Array^ Box2DShape::Vertices::get()
{
	if (_vertices == nullptr)
	{
		_vertices = gcnew Vector3Array(Native->getVertices(), 4);
	}
	return _vertices;
}

#endif
