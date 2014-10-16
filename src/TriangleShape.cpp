#include "StdAfx.h"

#if !defined(DISABLE_UNCOMMON) | !defined(DISABLE_GIMPACT)

#include "Collections.h"
#include "TriangleShape.h"

#define Native static_cast<btTriangleShape*>(_native)

TriangleShape::TriangleShape(btTriangleShape* native)
	: PolyhedralConvexShape(native)
{
}

TriangleShape::TriangleShape()
	: PolyhedralConvexShape(new btTriangleShape())
{
}

TriangleShape::TriangleShape(Vector3 point0, Vector3 point1, Vector3 point2)
	: PolyhedralConvexShape(0)
{
	VECTOR3_CONV(point0);
	VECTOR3_CONV(point1);
	VECTOR3_CONV(point2);
	UnmanagedPointer = new btTriangleShape(VECTOR3_USE(point0), VECTOR3_USE(point1), VECTOR3_USE(point2));
	VECTOR3_DEL(point0);
	VECTOR3_DEL(point1);
	VECTOR3_DEL(point2);
}

void TriangleShape::CalcNormal([Out] Vector3% normal)
{
	btVector3* normalTemp = ALIGNED_NEW(btVector3);
	Native->calcNormal(*normalTemp);
	Math::BtVector3ToVector3(normalTemp, normal);
	ALIGNED_FREE(normalTemp);
}

void TriangleShape::GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport)
{
	btVector3* planeNormalTemp = ALIGNED_NEW(btVector3);
	btVector3* planeSupportTemp = ALIGNED_NEW(btVector3);
	Native->getPlaneEquation(index, *planeNormalTemp, *planeSupportTemp);
	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);
	ALIGNED_FREE(planeNormalTemp);
	ALIGNED_FREE(planeSupportTemp);
}
/*
IntPtr TriangleShape::GetVertexPtr(int index)
{
	return IntPtr(&Native->getVertexPtr(index));
}
*/
Vector3Array^ TriangleShape::Vertices::get()
{
	if (_vertices == nullptr)
	{
		_vertices = gcnew Vector3Array(Native->m_vertices1, 3);
	}
	return _vertices;
}

#endif
