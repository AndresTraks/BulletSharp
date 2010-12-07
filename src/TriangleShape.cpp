#include "StdAfx.h"

#if !defined(DISABLE_UNCOMMON) | !defined(DISABLE_GIMPACT)

#include "Collections.h"
#include "TriangleShape.h"

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
	btVector3* p0Temp = Math::Vector3ToBtVector3(point0);
	btVector3* p1Temp = Math::Vector3ToBtVector3(point1);
	btVector3* p2Temp = Math::Vector3ToBtVector3(point2);

	UnmanagedPointer = new btTriangleShape(*p0Temp, *p1Temp, *p2Temp);

	delete p0Temp;
	delete p1Temp;
	delete p2Temp;
}

void TriangleShape::CalcNormal([Out] Vector3% normal)
{
	btVector3* normalTemp = new btVector3;
	UnmanagedPointer->calcNormal(*normalTemp);
	normal = Math::BtVector3ToVector3(normalTemp);
	delete normalTemp;
}

void TriangleShape::GetPlaneEquation(int index, [Out] Vector3% planeNormal, [Out] Vector3% planeSupport)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	UnmanagedPointer->getPlaneEquation(index, *planeNormalTemp, *planeSupportTemp);
	
	planeNormal = Math::BtVector3ToVector3(planeNormalTemp);
	planeSupport = Math::BtVector3ToVector3(planeSupportTemp);
	
	delete planeNormalTemp;
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
	TriangleShape_GetVertexPtr(UnmanagedPointer, index, vertexTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vertexTemp);
	delete vertexTemp;
	return vertex;
}

Vector3Array^ TriangleShape::Vertices::get()
{
	btVector3* vertices = UnmanagedPointer->m_vertices1;
	ReturnCachedObjectStatic(Vector3Array, _vertices, vertices, 3);
}

btTriangleShape* TriangleShape::UnmanagedPointer::get()
{
	return (btTriangleShape*)PolyhedralConvexShape::UnmanagedPointer;
}

#endif
