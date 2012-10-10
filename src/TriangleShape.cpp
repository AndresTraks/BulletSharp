#include "StdAfx.h"

#if !defined(DISABLE_UNCOMMON) | !defined(DISABLE_GIMPACT)

#include "Collections.h"
#include "TriangleShape.h"

#define Native static_cast<btTriangleShape*>(_native)

TriangleShape::TriangleShape(btTriangleShape* triangleShape)
: PolyhedralConvexShape(triangleShape)
{
}

TriangleShape::TriangleShape()
: PolyhedralConvexShape(new btTriangleShape())
{
}

TriangleShape::TriangleShape(Vector3 point0, Vector3 point1, Vector3 point2)
: PolyhedralConvexShape(0)
{
	VECTOR3_DEF(point0);
	VECTOR3_DEF(point1);
	VECTOR3_DEF(point2);

	UnmanagedPointer = new btTriangleShape(VECTOR3_USE(point0), VECTOR3_USE(point1), VECTOR3_USE(point2));

	VECTOR3_DEL(point0);
	VECTOR3_DEL(point1);
	VECTOR3_DEL(point2);
}

void TriangleShape::CalcNormal([Out] Vector3% normal)
{
	btVector3* normalTemp = new btVector3;
	Native->calcNormal(*normalTemp);
	Math::BtVector3ToVector3(normalTemp, normal);
	delete normalTemp;
}

void TriangleShape::GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	Native->getPlaneEquation(index, *planeNormalTemp, *planeSupportTemp);
	
	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);
	
	delete planeNormalTemp;
	delete planeSupportTemp;
}

#pragma managed(push, off)
void TriangleShape_GetVertexPtr(btTriangleShape* shape, int index, btVector3* vertex)
{
	*vertex = shape->getVertexPtr(index);
}
#pragma managed(pop)
Vector3 TriangleShape::GetVertexPtr(int index)
{
	btVector3* vertexTemp = new btVector3;
	TriangleShape_GetVertexPtr(Native, index, vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	delete vertexTemp;
	return vertex;
}

Vector3Array^ TriangleShape::Vertices::get()
{
	btVector3* vertices = Native->m_vertices1;
	ReturnCachedObjectStaticParam(Vector3Array, _vertices, vertices, 3);
}

#endif
